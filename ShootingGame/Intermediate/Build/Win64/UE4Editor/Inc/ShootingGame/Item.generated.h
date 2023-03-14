// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef SHOOTINGGAME_Item_generated_h
#error "Item.generated.h already included, missing '#pragma once' in Item.h"
#endif
#define SHOOTINGGAME_Item_generated_h

#define ShootingGame_Source_ShootingGame_Item_h_12_SPARSE_DATA
#define ShootingGame_Source_ShootingGame_Item_h_12_RPC_WRAPPERS
#define ShootingGame_Source_ShootingGame_Item_h_12_RPC_WRAPPERS_NO_PURE_DECLS
#define ShootingGame_Source_ShootingGame_Item_h_12_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAItem(); \
	friend struct Z_Construct_UClass_AItem_Statics; \
public: \
	DECLARE_CLASS(AItem, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/ShootingGame"), NO_API) \
	DECLARE_SERIALIZER(AItem)


#define ShootingGame_Source_ShootingGame_Item_h_12_INCLASS \
private: \
	static void StaticRegisterNativesAItem(); \
	friend struct Z_Construct_UClass_AItem_Statics; \
public: \
	DECLARE_CLASS(AItem, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/ShootingGame"), NO_API) \
	DECLARE_SERIALIZER(AItem)


#define ShootingGame_Source_ShootingGame_Item_h_12_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AItem(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AItem) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AItem); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AItem); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AItem(AItem&&); \
	NO_API AItem(const AItem&); \
public:


#define ShootingGame_Source_ShootingGame_Item_h_12_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AItem(AItem&&); \
	NO_API AItem(const AItem&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AItem); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AItem); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AItem)


#define ShootingGame_Source_ShootingGame_Item_h_12_PRIVATE_PROPERTY_OFFSET
#define ShootingGame_Source_ShootingGame_Item_h_9_PROLOG
#define ShootingGame_Source_ShootingGame_Item_h_12_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	ShootingGame_Source_ShootingGame_Item_h_12_PRIVATE_PROPERTY_OFFSET \
	ShootingGame_Source_ShootingGame_Item_h_12_SPARSE_DATA \
	ShootingGame_Source_ShootingGame_Item_h_12_RPC_WRAPPERS \
	ShootingGame_Source_ShootingGame_Item_h_12_INCLASS \
	ShootingGame_Source_ShootingGame_Item_h_12_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define ShootingGame_Source_ShootingGame_Item_h_12_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	ShootingGame_Source_ShootingGame_Item_h_12_PRIVATE_PROPERTY_OFFSET \
	ShootingGame_Source_ShootingGame_Item_h_12_SPARSE_DATA \
	ShootingGame_Source_ShootingGame_Item_h_12_RPC_WRAPPERS_NO_PURE_DECLS \
	ShootingGame_Source_ShootingGame_Item_h_12_INCLASS_NO_PURE_DECLS \
	ShootingGame_Source_ShootingGame_Item_h_12_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> SHOOTINGGAME_API UClass* StaticClass<class AItem>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID ShootingGame_Source_ShootingGame_Item_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
