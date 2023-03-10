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
// Base Rates for turning/Looking up
	:BaseTurnRate(90.f)
	, BaseLookUpRate(90.f)
	// Turn rates for aiming/not aiming
	, HipTurnRate(90.f)
	, HipLookUpRate(90.f)
	, AimingTurnRate(20.f)
	, AimingLookUpRate(20.f)
	// Mouse Look sensitivity scale factors
	, MouseHipTurnRate(1.0f)
	, MouseHipLookUpRate(1.0f)
	, MouseAimingTurnRate(0.2f)
	, MouseAimingLookUpRate(0.2f)
	// true when aiming weapon
	, bAiming(false)
	// Camera FOV Values
	, CameraDefaultFOV(0.f) // Set in BeginPlay
	, CameraZoomedFOV(35.f)
	, CameraCurrentFOV(0.f)
	, ZoomInterpSpeed(20.0f)
	// Crosshair Spread Factors
	, CrosshairSpreadMultiplier(0.f)
	, CrosshairVelocityFactor(0.f)
	, CrosshairInAirFactor(0.f)
	, CrosshairAimFactor(0.f)
	, CrosshairShootingFactor(0.f)
	// Bullet Fire timer Variables
	, ShootTimeDuration(0.05f)
	, bFiringBullet(false)
	// HUD Crosshair Correction Value
	, CorrectionValueCrossHairZ(0.0f)
	// Automatic fire variables
	, AutomaticFireRate(0.1f)
	, bShouldFire(true)
	, bFireButtonPressed(false)
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
	//33. ????
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
	// BaseTurn Rate == ???? ?????? ????
	// ???? ?????? ?????????? ???? ?????? ???????? ???? ???? ?????? ?????????
	
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());

}

void AShooterCharacter::LookUpAtRate(float Rate)
{
	// deg/sec * sec/frame
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());

}

void AShooterCharacter::Turn(float Value)
{
	float TurnScaleFactor{};
	if (bAiming)
	{
		TurnScaleFactor = MouseAimingTurnRate;
	}
	else
	{
		TurnScaleFactor = MouseHipTurnRate;
	}
	AddControllerYawInput(Value * TurnScaleFactor);
}

void AShooterCharacter::LookUp(float Value)
{
	float LookUpScaleFactor{};
	if (bAiming)
	{
		LookUpScaleFactor = MouseAimingLookUpRate;
	}
	else
	{
		LookUpScaleFactor = MouseHipLookUpRate;
	}
	AddControllerPitchInput(Value * LookUpScaleFactor);
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

	// Start Bullet Fire timer for crosshairs
	StartCrosshairBulletFire();

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
	CrosshairLocation.Y -= CorrectionValueCrossHairZ;
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
	{
		CameraCurrentFOV = FMath::FInterpTo(CameraCurrentFOV, CameraZoomedFOV, Deltatime, ZoomInterpSpeed);
	}
	else// Interpolate to defualt FOV
	{
		CameraCurrentFOV = FMath::FInterpTo(CameraCurrentFOV, CameraDefaultFOV, Deltatime, ZoomInterpSpeed);
	}
	GetFollowCamera()->SetFieldOfView(CameraCurrentFOV);
}

void AShooterCharacter::SetLookRates()
{
	if (bAiming)
	{
		BaseTurnRate = AimingTurnRate;
		BaseLookUpRate = AimingLookUpRate;
		
	}
	else
	{
		BaseTurnRate = HipTurnRate;
		BaseLookUpRate = HipLookUpRate;
	}
}

void AShooterCharacter::CalculateCrosshairSpread(float DeltaTime)
{
	FVector2D WalkSpeedRange{ 0.f,600.f };
	FVector2D VelocityMultiplierRange{ 0.f,1.f };
	FVector Velocity{ GetVelocity() };
	Velocity.Z = 0;
	// Caculate Crosshair Velocity Factor
	CrosshairVelocityFactor = FMath::GetMappedRangeValueClamped(WalkSpeedRange, VelocityMultiplierRange, Velocity.Size());

	// Caculate Crosshair in air Factor
	if (GetCharacterMovement()->IsFalling())
	{
		// Spread the crosshairs slowly while in air
		CrosshairInAirFactor = FMath::FInterpTo(CrosshairInAirFactor, 2.25f, DeltaTime, 2.25f);
	}
	else // Character is on the ground
	{
		// Shrink the crosshairs rapidly while on the ground
		CrosshairInAirFactor = FMath::FInterpTo(CrosshairInAirFactor, 0.0f, DeltaTime, 30.0f);
	}

	// Caculate Crosshair Aim Factor
	if (bAiming) // Are we Aiming?
	{
		// Shrink the crosshairs a small amount very quickly
		CrosshairAimFactor = FMath::FInterpTo(CrosshairAimFactor, 0.5f, DeltaTime, 30.f);
	}
	else
	{
		// Spread crosshairs back to normal very quickly
		CrosshairAimFactor = FMath::FInterpTo(CrosshairAimFactor, 0.0f, DeltaTime, 30.f);
	}

	// True 0.05f Second after Firing
	if (bFiringBullet)
	{
		CrosshairShootingFactor = FMath::FInterpTo(CrosshairShootingFactor, 0.3f, DeltaTime, 60.0f);
	}
	else
	{
		CrosshairShootingFactor = FMath::FInterpTo(CrosshairShootingFactor, 0.0f, DeltaTime, 60.0f);
	}

	CrosshairSpreadMultiplier = 0.5f + CrosshairVelocityFactor + CrosshairInAirFactor - CrosshairAimFactor + CrosshairShootingFactor;
}

void AShooterCharacter::StartCrosshairBulletFire()
{
	bFiringBullet = true;

	GetWorldTimerManager().SetTimer(CrosshairShootTimer, this, &AShooterCharacter::FinishCrosshairBulletFire, ShootTimeDuration);
}

void AShooterCharacter::FinishCrosshairBulletFire()
{
	bFiringBullet = false;

}

void AShooterCharacter::FireButtonPressed()
{
	bFireButtonPressed = true;
	StartFireTimer();
}

void AShooterCharacter::FireButtonReleased()
{
	bFireButtonPressed = false;
}

void AShooterCharacter::StartFireTimer()
{
	if (bShouldFire)
	{
		FireWeapon();
		bShouldFire = false;
		GetWorldTimerManager().SetTimer(AutoFireTimer, this, &AShooterCharacter::AutoFireReset, AutomaticFireRate);
	}
}

void AShooterCharacter::AutoFireReset()
{
	bShouldFire = true;
	if (bFireButtonPressed)
	{
		StartFireTimer();
	}
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CameraZoomInOut(DeltaTime);

	//Change Look sensitivity based on aiming
	SetLookRates();
	// Caculate crosshair spread multiplier
	CalculateCrosshairSpread(DeltaTime);
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

	PlayerInputComponent->BindAxis("Turn", this, &AShooterCharacter::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &AShooterCharacter::LookUp);

	// ?????? ???????? ???????????? ?????? ??????
	PlayerInputComponent->BindAction("Jump", IE_Pressed,this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("FireButton", IE_Pressed, this, &AShooterCharacter::FireButtonPressed);
	PlayerInputComponent->BindAction("FireButton", IE_Released, this, &AShooterCharacter::FireButtonReleased);


	PlayerInputComponent->BindAction("AimingButton", IE_Pressed, this, &AShooterCharacter::AimingButtonPressed);
	PlayerInputComponent->BindAction("AimingButton", IE_Released, this, &AShooterCharacter::AimingButtonReleased);
}
float AShooterCharacter::GetCrosshairSpreadMultiplier() const
{
	return CrosshairSpreadMultiplier;
}

float AShooterCharacter::GetCorrectionValueCrossHairZ() const
{
	return CorrectionValueCrossHairZ;
}


