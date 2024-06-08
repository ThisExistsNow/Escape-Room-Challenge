// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EscapeGameModeBase.generated.h"


/**
 * Forward Declarations
 */
class ACharacter_Controller;

UCLASS()
class ESCAPE_API AEscapeGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
	ACharacter_Controller* pawn;
public:
	AEscapeGameModeBase();

	class UDataTable* GetItemsDB() const { return ItemsDB; }

protected:

	UPROPERTY(EditDefaultsOnly)
		class UDataTable* ItemsDB;
};
