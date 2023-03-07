// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

UCLASS()
class SHOOTINGGAME_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	// Called for forwards/backwards input
	void MoveForward(float Value);

	// Called for side to side input
	void MoveRight(float Value);

	// Called via input to turn at a given rate
	// 정해진 속도로 돌기 위한 함수. 
	// @param Rate	This is a normalized rate , i.e. 1.0 means 100% desired turn rate
	// 매개변수 Rate 는 회전률의 평균값이다 . 1% 는 100% 최대속도 회전값이다.
	void TurnAtRate(float Rate);
	// Called via input to look up/down at a given rate
	// @param Rate	This is a normalized rate , i.e. 1.0 means 100% of desired rate
	void LookUpAtRate(float Rate);

	// Rotate Controller based on mouse X movement
	// @param Value The input Value from mouse movement
	void Turn(float Value);
	// Rotate Controller based on mouse Y movement
	// @param Value The input Value from mouse movement
	void LookUp(float Value);

	// Called when the Fire button is pressed
	void FireWeapon();

	bool GetBeamEndLocation(const FVector& MuzzleSocketLocation, FVector& OutBeamLocation);

	// Set bAming true or false with button press
	void AimingButtonPressed();
	void AimingButtonReleased();

	void CameraZoomInOut(const float Deltatime);
	// Set BaseTurnRate and BaseLookUpRate Based on aiming
	void SetLookRates();

	void CalculateCrosshairSpread(float DeltaTime);

	void StartCrosshairBulletFire();

	UFUNCTION()
	void FinishCrosshairBulletFire();

	void FireButtonPressed();
	void FireButtonReleased();

	void StartFireTimer();
	UFUNCTION()
	void AutoFireReset();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


private:

	// Camera boom positioning the camera behind the character
	UPROPERTY(VisibleAnywhere , BlueprintReadOnly,Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	// Camera that follows the character
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	// Base Turn Rate , in degree/second . Ohter scaling may affect final turn rate
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = Camera, meta = (AllowPrivateAccess = "true"))
	float BaseTurnRate;

	// Base Look up/down rate , in deg/sec. Other sacling may affect final turn rate
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	float BaseLookUpRate;

	// TurnRate while not Aiming
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	float HipTurnRate;
	// Look Up when Not Aiming
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	float HipLookUpRate;
	// Turn rate when Aiming
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	float AimingTurnRate;
	//Look Up rate when Aiming
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	float AimingLookUpRate;

	// Scale Factor for mouse look sensitivity. Turn rate when not aiming.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"), meta = (ClampMin = "0.0",ClampMax = "1.0",UIMin = "0.0",UIMax = "1.0"))
	float MouseHipTurnRate;
	// Scale Factor for mouse look sensitivity. Look up rate when not aiming.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"), meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
	float MouseHipLookUpRate;

	// Scale Factor for mouse look sensitivity. Turn rate when aiming.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"), meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
	float MouseAimingTurnRate;
	// Scale Factor for mouse look sensitivity. Turn rate when not aiming.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"), meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
	float MouseAimingLookUpRate;
	

	// Randomized gunshot sound cue
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = Combat , meta = (AllowPrivateAccess = "true"))
	class USoundCue* FireSound;

	// Flash Spawned at BarrelSocket
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AllowPrivateAccess = "true"))
	class UParticleSystem* MuzzleFlash;

	// Mongate for firing the weapon
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AllowPrivateAccess = "true"))
	class UAnimMontage* HipFireMontage;
	
	// Particles spawn upon bullet impact 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AllowPrivateAccess = "true"))
	UParticleSystem* ImpactParticles;

	// Smoke Trail for bullets
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AllowPrivateAccess = "true"))
	UParticleSystem* BeamParticles;

	// True when Aiming
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = Combat,meta = (AllowPrivateAccess = "true"))
	bool bAiming;

	// Default camera field of view value
	float CameraDefaultFOV;

	// Field of View value for when zoomed in
	float CameraZoomedFOV;

	// Current Field of view this frame
	float CameraCurrentFOV;

	// Interp Speed for Zooming when Aiming
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AllowPrivateAccess = "true"))
	float ZoomInterpSpeed;

	// Detetermines the spread of the crosshairs
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Crosshairs, meta = (AllowPrivateAccess = "true"))
	float CrosshairSpreadMultiplier;
	// Velocity component for crosshairs spread
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Crosshairs, meta = (AllowPrivateAccess = "true"))
	float CrosshairVelocityFactor;
	// In Air component for crosshairs spread
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Crosshairs, meta = (AllowPrivateAccess = "true"))
	float CrosshairInAirFactor;
	// Aim component for crosshairs spread
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Crosshairs, meta = (AllowPrivateAccess = "true"))
	float CrosshairAimFactor;
	// Shooting component for crosshairs spread
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Crosshairs, meta = (AllowPrivateAccess = "true"))
	float CrosshairShootingFactor;

	float ShootTimeDuration;
	bool bFiringBullet;
	FTimerHandle CrosshairShootTimer;

	// MVAT Aiming Correction Value
	// 추후에 이건 옵션으로 빼야하지 않을까??
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = HUD, meta = (AllowPrivateAccess = "true"))
		float CorrectionValueCrossHairZ;

	// Left Mouse Button or right console trigger pressed
	bool bFireButtonPressed;

	// True when we can fire. False when waiting for the timer
	bool bShouldFire;

	// Rate of automatic gun fire
	float AutomaticFireRate;

	// Sets a Timer between GunShot
	FTimerHandle AutoFireTimer;

public:
	// Returns CameraBoom subobject
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	// Returns Follow Camera subobject
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }


	FORCEINLINE bool GetIsAiming() const { return bAiming; }

	UFUNCTION(BlueprintCallable)
	float GetCrosshairSpreadMultiplier()const;

	UFUNCTION(BlueprintCallable)
		float GetCorrectionValueCrossHairZ()const;
};
