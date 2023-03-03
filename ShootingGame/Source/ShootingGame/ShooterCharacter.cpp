// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Particles/ParticleSystemComponent.h"

#include "DrawDebugHelpers.h"
// Sets default values
AShooterCharacter::AShooterCharacter()
	:BaseTurnRate(90.f)
	,BaseLookUpRate(90.f)
	,bAiming(false)
	, CameraDefaultFOV(0.f) // Set in BeginPlay
	, CameraZoomedFOV(35.f)
	, CameraCurrentFOV(0.f)
	,ZoomInterpSpeed(20.0f)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a CameraBoom (pulls in towards the character if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	// Setup Camera
	CameraBoom->SetupAttachment(RootComponent);

	// The Camera follows at this distance behind the character
	CameraBoom->TargetArmLength = 180.0f;
	// Rotate the arm based on the controller
	CameraBoom->bUsePawnControlRotation = true;


	CameraBoom->SocketOffset = FVector(0.f, 50.f, 70.f);

	// Create a Foolow Camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	// Attach camera to end of
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	// Camera doesn't rotate relative to arm
	FollowCamera->bUsePawnControlRotation = false;

	// Don't Rotate when the controller rotates. Let the controller only affect the camaera.
	bUseControllerRotationPitch = false;
	//33. 수정
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;
	
	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = false; // character moves in the direction of input ...
	GetCharacterMovement()->RotationRate = FRotator(0.f, 560.f, 0.f); // ... at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.0f;
	GetCharacterMovement()->AirControl = 0.2f;
}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (FollowCamera)
	{
		CameraDefaultFOV = GetFollowCamera()->FieldOfView;
		CameraCurrentFOV = CameraDefaultFOV;
	}
}

void AShooterCharacter::MoveForward(float Value)
{
	if ((nullptr != Controller) && (0.0f != Value))
	{
		// find out which way is forward
		const FRotator Rotation{ Controller->GetControlRotation() };
		const FRotator YawRotation{ 0,Rotation.Yaw,0 };

		const FVector Direction{ FRotationMatrix{YawRotation}.GetUnitAxis(EAxis::X) };
		//UE_LOG(LogTemp, Warning, TEXT("VecSize : %.5f"), Direction.Size());

		AddMovementInput(Direction, Value);
	}
}

void AShooterCharacter::MoveRight(float Value)
{
	if ((nullptr != Controller) && (0.0f != Value))
	{
		// find out which way is forward
		const FRotator Rotation{ Controller->GetControlRotation() };
		const FRotator YawRotation{ 0,Rotation.Yaw,0 };

		const FVector Direction{ FRotationMatrix{YawRotation}.GetUnitAxis(EAxis::Y) };
		AddMovementInput(Direction, Value);
	}
}

void AShooterCharacter::TurnAtRate(float Rate)
{
	// deg/sec * sec/frame
	// BaseTurn Rate == 초당 회전할 각도
	// 뭔가 나중에 설정값으로 회전 감도를 설정하기 위해 해당 설정을 하는건가?
	
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());

}

void AShooterCharacter::LookUpAtRate(float Rate)
{
	// deg/sec * sec/frame
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());

}

void AShooterCharacter::FireWeapon()
{
	UE_LOG(LogTemp, Warning, TEXT("Fire Weapon."));
	if (FireSound)
		UGameplayStatics::PlaySound2D(this, FireSound);

	const USkeletalMeshSocket* BarrelSocket = GetMesh()->GetSocketByName("Barrel");
	if (BarrelSocket)
	{
		const FTransform SocketTransform = BarrelSocket->GetSocketTransform(GetMesh());
		
		if (MuzzleFlash)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), MuzzleFlash, SocketTransform);
		}

		FVector BeamEnd;
		bool bBeamEnd = GetBeamEndLocation(SocketTransform.GetLocation(), BeamEnd);
		if (bBeamEnd)
		{
			if (ImpactParticles)
			{
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactParticles, BeamEnd);
			}

			UParticleSystemComponent* Beam = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), BeamParticles, SocketTransform);
			if (Beam)
			{
				Beam->SetVectorParameter(FName("Target"), BeamEnd);
			}
		}
	}
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && HipFireMontage)
	{
		AnimInstance->Montage_Play(HipFireMontage);
		AnimInstance->Montage_JumpToSection(FName("StartFire"));
	}

}

bool AShooterCharacter::GetBeamEndLocation(const FVector& MuzzleSocketLocation, FVector& OutBeamLocation)
{
	// Get Current size of the view port
	FVector2D ViewportSize;
	if (GEngine && GEngine->GameViewport)
	{
		GEngine->GameViewport->GetViewportSize(ViewportSize);
	}

	//Get Screen space of crosshairs
	FVector2D CrosshairLocation(ViewportSize.X / 2.f, ViewportSize.Y / 2.f);
	CrosshairLocation.Y -= 50.0f;
	FVector CrosshairWorldPosition;
	FVector CrosshairWorldDirection;

	//Get World position and direction of crosshairs
	bool bScreenToWorld = UGameplayStatics::DeprojectScreenToWorld(UGameplayStatics::GetPlayerController(this, 0)
		, CrosshairLocation
		, CrosshairWorldPosition
		, CrosshairWorldDirection);

	// was deprojection successful?
	if (bScreenToWorld)
	{
		FHitResult ScreenTraceHit;
		const FVector Start{ CrosshairWorldPosition };
		const FVector End{ CrosshairWorldPosition + CrosshairWorldDirection * 50'000.f };

		// Set beam end point  to line trace end point
		OutBeamLocation = End;

		// Trace outward from crosshairs world location
		GetWorld()->LineTraceSingleByChannel(ScreenTraceHit
			, Start
			, End
			, ECollisionChannel::ECC_Visibility);
		// was ther a tarce hit?
		if (ScreenTraceHit.bBlockingHit)
		{
			// Beam end point is now trace hit location
			OutBeamLocation = ScreenTraceHit.Location;
		}

		// Perform a second trace , this tim from the gun barrel
		FHitResult WeaponTraceHit;
		const FVector WeaponTraceStart{ MuzzleSocketLocation };
		const FVector WeaponTraceEnd{ OutBeamLocation };
		GetWorld()->LineTraceSingleByChannel(WeaponTraceHit
			, WeaponTraceStart
			, WeaponTraceEnd
			, ECollisionChannel::ECC_Visibility);
		// Object between barrel and BeamEndPoint?
		if (WeaponTraceHit.bBlockingHit)
			OutBeamLocation = WeaponTraceHit.Location;
		
		return true;
	}

	return false;
}

void AShooterCharacter::AimingButtonPressed()
{
	bAiming = true;

	//GetFollowCamera()->SetFieldOfView(CameraZoomedFOV);

}

void AShooterCharacter::AimingButtonReleased()
{
	bAiming = false;

	//GetFollowCamera()->SetFieldOfView(CameraDefaultFOV);
}

void AShooterCharacter::CameraZoomInOut(const float Deltatime)
{	
	// Set Current Camera FOV
	if (bAiming)// Interpolate to zoomed FOV
		CameraCurrentFOV = FMath::FInterpTo(CameraCurrentFOV, CameraZoomedFOV, Deltatime, ZoomInterpSpeed);
	else// Interpolate to defualt FOV
		CameraCurrentFOV = FMath::FInterpTo(CameraCurrentFOV, CameraDefaultFOV, Deltatime, ZoomInterpSpeed);
	GetFollowCamera()->SetFieldOfView(CameraCurrentFOV);

}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CameraZoomInOut(DeltaTime);

}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward",this, &AShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AShooterCharacter::MoveRight);

	PlayerInputComponent->BindAxis("TurnRate", this, &AShooterCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AShooterCharacter::LookUpAtRate);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	// 캐릭터 클래스에 구현되어있는 점프를 넣는다
	PlayerInputComponent->BindAction("Jump", IE_Pressed,this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("FireButton", IE_Pressed, this, &AShooterCharacter::FireWeapon);

	PlayerInputComponent->BindAction("AimingButton", IE_Pressed, this, &AShooterCharacter::AimingButtonPressed);
	PlayerInputComponent->BindAction("AimingButton", IE_Released, this, &AShooterCharacter::AimingButtonReleased);
} 

