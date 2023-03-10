// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef SHOOTINGGAME_ShooterCharacter_generated_h
#error "ShooterCharacter.generated.h already included, missing '#pragma once' in ShooterCharacter.h"
#endif
#define SHOOTINGGAME_ShooterCharacter_generated_h

#define ShootingGame_Source_ShootingGame_ShooterCharacter_h_12_SPARSE_DATA
#define ShootingGame_Source_ShootingGame_ShooterCharacter_h_12_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execGetCorrectionValueCrossHairZ); \
	DECLARE_FUNCTION(execGetCrosshairSpreadMultiplier); \
	DECLARE_FUNCTION(execAutoFireReset); \
	DECLARE_FUNCTION(execFinishCrosshairBulletFire);


#define ShootingGame_Source_ShootingGame_ShooterCharacter_h_12_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execGetCorrectionValueCrossHairZ); \
	DECLARE_FUNCTION(execGetCrosshairSpreadMultiplier); \
	DECLARE_FUNCTION(execAutoFireReset); \
	DECLARE_FUNCTION(execFinishCrosshairBulletFire);


#define ShootingGame_Source_ShootingGame_ShooterCharacter_h_12_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAShooterCharacter(); \
	friend struct Z_Construct_UClass_AShooterCharacter_Statics; \
public: \
	DECLARE_CLASS(AShooterCharacter, ACharacter, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/ShootingGame"), NO_API) \
	DECLARE_SERIALIZER(AShooterCharacter)


#define ShootingGame_Source_ShootingGame_ShooterCharacter_h_12_INCLASS \
private: \
	static void StaticRegisterNativesAShooterCharacter(); \
	friend struct Z_Construct_UClass_AShooterCharacter_Statics; \
public: \
	DECLARE_CLASS(AShooterCharacter, ACharacter, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/ShootingGame"), NO_API) \
	DECLARE_SERIALIZER(AShooterCharacter)


#define ShootingGame_Source_ShootingGame_ShooterCharacter_h_12_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AShooterCharacter(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AShooterCharacter) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AShooterCharacter); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AShooterCharacter); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AShooterCharacter(AShooterCharacter&&); \
	NO_API AShooterCharacter(const AShooterCharacter&); \
public:


#define ShootingGame_Source_ShootingGame_ShooterCharacter_h_12_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AShooterCharacter(AShooterCharacter&&); \
	NO_API AShooterCharacter(const AShooterCharacter&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AShooterCharacter); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AShooterCharacter); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AShooterCharacter)


#define ShootingGame_Source_ShootingGame_ShooterCharacter_h_12_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__CameraBoom() { return STRUCT_OFFSET(AShooterCharacter, CameraBoom); } \
	FORCEINLINE static uint32 __PPO__FollowCamera() { return STRUCT_OFFSET(AShooterCharacter, FollowCamera); } \
	FORCEINLINE static uint32 __PPO__BaseTurnRate() { return STRUCT_OFFSET(AShooterCharacter, BaseTurnRate); } \
	FORCEINLINE static uint32 __PPO__BaseLookUpRate() { return STRUCT_OFFSET(AShooterCharacter, BaseLookUpRate); } \
	FORCEINLINE static uint32 __PPO__HipTurnRate() { return STRUCT_OFFSET(AShooterCharacter, HipTurnRate); } \
	FORCEINLINE static uint32 __PPO__HipLookUpRate() { return STRUCT_OFFSET(AShooterCharacter, HipLookUpRate); } \
	FORCEINLINE static uint32 __PPO__AimingTurnRate() { return STRUCT_OFFSET(AShooterCharacter, AimingTurnRate); } \
	FORCEINLINE static uint32 __PPO__AimingLookUpRate() { return STRUCT_OFFSET(AShooterCharacter, AimingLookUpRate); } \
	FORCEINLINE static uint32 __PPO__MouseHipTurnRate() { return STRUCT_OFFSET(AShooterCharacter, MouseHipTurnRate); } \
	FORCEINLINE static uint32 __PPO__MouseHipLookUpRate() { return STRUCT_OFFSET(AShooterCharacter, MouseHipLookUpRate); } \
	FORCEINLINE static uint32 __PPO__MouseAimingTurnRate() { return STRUCT_OFFSET(AShooterCharacter, MouseAimingTurnRate); } \
	FORCEINLINE static uint32 __PPO__MouseAimingLookUpRate() { return STRUCT_OFFSET(AShooterCharacter, MouseAimingLookUpRate); } \
	FORCEINLINE static uint32 __PPO__FireSound() { return STRUCT_OFFSET(AShooterCharacter, FireSound); } \
	FORCEINLINE static uint32 __PPO__MuzzleFlash() { return STRUCT_OFFSET(AShooterCharacter, MuzzleFlash); } \
	FORCEINLINE static uint32 __PPO__HipFireMontage() { return STRUCT_OFFSET(AShooterCharacter, HipFireMontage); } \
	FORCEINLINE static uint32 __PPO__ImpactParticles() { return STRUCT_OFFSET(AShooterCharacter, ImpactParticles); } \
	FORCEINLINE static uint32 __PPO__BeamParticles() { return STRUCT_OFFSET(AShooterCharacter, BeamParticles); } \
	FORCEINLINE static uint32 __PPO__bAiming() { return STRUCT_OFFSET(AShooterCharacter, bAiming); } \
	FORCEINLINE static uint32 __PPO__ZoomInterpSpeed() { return STRUCT_OFFSET(AShooterCharacter, ZoomInterpSpeed); } \
	FORCEINLINE static uint32 __PPO__CrosshairSpreadMultiplier() { return STRUCT_OFFSET(AShooterCharacter, CrosshairSpreadMultiplier); } \
	FORCEINLINE static uint32 __PPO__CrosshairVelocityFactor() { return STRUCT_OFFSET(AShooterCharacter, CrosshairVelocityFactor); } \
	FORCEINLINE static uint32 __PPO__CrosshairInAirFactor() { return STRUCT_OFFSET(AShooterCharacter, CrosshairInAirFactor); } \
	FORCEINLINE static uint32 __PPO__CrosshairAimFactor() { return STRUCT_OFFSET(AShooterCharacter, CrosshairAimFactor); } \
	FORCEINLINE static uint32 __PPO__CrosshairShootingFactor() { return STRUCT_OFFSET(AShooterCharacter, CrosshairShootingFactor); } \
	FORCEINLINE static uint32 __PPO__CorrectionValueCrossHairZ() { return STRUCT_OFFSET(AShooterCharacter, CorrectionValueCrossHairZ); }


#define ShootingGame_Source_ShootingGame_ShooterCharacter_h_9_PROLOG
#define ShootingGame_Source_ShootingGame_ShooterCharacter_h_12_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	ShootingGame_Source_ShootingGame_ShooterCharacter_h_12_PRIVATE_PROPERTY_OFFSET \
	ShootingGame_Source_ShootingGame_ShooterCharacter_h_12_SPARSE_DATA \
	ShootingGame_Source_ShootingGame_ShooterCharacter_h_12_RPC_WRAPPERS \
	ShootingGame_Source_ShootingGame_ShooterCharacter_h_12_INCLASS \
	ShootingGame_Source_ShootingGame_ShooterCharacter_h_12_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define ShootingGame_Source_ShootingGame_ShooterCharacter_h_12_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	ShootingGame_Source_ShootingGame_ShooterCharacter_h_12_PRIVATE_PROPERTY_OFFSET \
	ShootingGame_Source_ShootingGame_ShooterCharacter_h_12_SPARSE_DATA \
	ShootingGame_Source_ShootingGame_ShooterCharacter_h_12_RPC_WRAPPERS_NO_PURE_DECLS \
	ShootingGame_Source_ShootingGame_ShooterCharacter_h_12_INCLASS_NO_PURE_DECLS \
	ShootingGame_Source_ShootingGame_ShooterCharacter_h_12_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> SHOOTINGGAME_API UClass* StaticClass<class AShooterCharacter>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID ShootingGame_Source_ShootingGame_ShooterCharacter_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
