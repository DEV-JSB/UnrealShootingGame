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

	// Called when the Fire button is pressed
	void FireWeapon();


	bool GetBeamEndLocation(const FVector& MuzzleSocketLocation, FVector& OutBeamLocation);

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


public:
	// Returns CameraBoom subobject
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	// Returns Follow Camera subobject
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }

};
