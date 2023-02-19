// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"

// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	UE_LOG(LogTemp, Warning, TEXT("BeginPlay() Called!"));

	int myInt{ 42 };

	UE_LOG(LogTemp, Warning, TEXT("int myInt : %d"), myInt);

	float myFloat{ 3.14159f };
	UE_LOG(LogTemp, Warning, TEXT("float myFloat : %f"), myFloat);

	double myDouble{ 0.000756 };
	UE_LOG(LogTemp, Warning, TEXT("double myDouble : %lf"), myDouble);

	char myChar{ 'J' };
	UE_LOG(LogTemp, Warning, TEXT("char myChar : %c"), myChar);

	wchar_t widechar{ L'J' };
	UE_LOG(LogTemp, Warning, TEXT("wchar_t widechar : %lc"), myFloat);

	bool myBool{ true };
	UE_LOG(LogTemp, Warning, TEXT("bool myBool : %d"), myBool);

	UE_LOG(LogTemp, Warning, TEXT("int : %d , float : %f , bool : %d"), myInt,myFloat,myBool);

	FString myString{ TEXT("My String!!!!") };
	// 포인터가 아니라 Overload 를 넘긴다고 한다,출력로그에 FString 을 출력하려면 * 이 필요하다.
	UE_LOG(LogTemp, Warning, TEXT("FString myString : %s"), *myString);

	UE_LOG(LogTemp, Warning, TEXT("Name of instance : %s"), *GetName());

}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

