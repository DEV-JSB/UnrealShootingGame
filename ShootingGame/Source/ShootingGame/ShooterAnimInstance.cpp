// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ShooterCharacter.h"
#include "Kismet/KismetMathLibrary.h"

void UShooterAnimInstance::UpdateAnimationProperties(float DeltaTime)
{
	if (nullptr == ShooterCharacter)
	{
		ShooterCharacter = Cast<AShooterCharacter>(TryGetPawnOwner());
	}
	if (ShooterCharacter)
	{
		// Get the lateral Speed of the character from velocity
		FVector Velocity{ ShooterCharacter->GetVelocity() };
		Velocity.Z = 0;
		Speed = Velocity.Size();

		// Is the character in the air?
		bIsInAir = ShooterCharacter->GetCharacterMovement()->IsFalling();

		// Is the character accelerating?
		// 가속도를 구해서 만약 가속이 0이라면 캐릭터는 움직이지 않는다고 판별한다.
		if (0 < ShooterCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size())
			bIsAccelerating = true;
		else
			bIsAccelerating = false;


		FRotator AimRotation = ShooterCharacter->GetBaseAimRotation();
		FRotator MovementRotation = UKismetMathLibrary::MakeRotFromX(ShooterCharacter->GetVelocity());

		MovementOffsetYaw = UKismetMathLibrary::NormalizedDeltaRotator(MovementRotation, AimRotation).Yaw;

		if(0.f < ShooterCharacter->GetVelocity().Size())
			LastMovementOffsetYaw = MovementOffsetYaw;


		bAiming = ShooterCharacter->GetIsAiming();

		/*
		FString RotationMessage = FString::Printf(TEXT("Base Aim Rotation : %f"), AimRotation.Yaw);
		FString MovementRotationMessage = FString::Printf(TEXT("Movement Rotation : %f"), MovementRotation.Yaw);
		FString OffsetMessage = FString::Printf(TEXT("MovementOffset Yaw : %f"), MovementOffsetYaw);
		if (GEngine)
		{
			//GEngine->AddOnScreenDebugMessage(1, 0.f, FColor::White, RotationMessage);
			//GEngine->AddOnScreenDebugMessage(1, 0.f, FColor::White, MovementRotationMessage);

			GEngine->AddOnScreenDebugMessage(1, 0.f, FColor::White, OffsetMessage);

		}*/
	}

}

void UShooterAnimInstance::NativeInitializeAnimation()
{
	ShooterCharacter = Cast<AShooterCharacter>(TryGetPawnOwner());


}
