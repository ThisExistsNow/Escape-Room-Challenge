// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "Components/InputComponent.h"
#include "Engine/DataTable.h"
#include "Engine/World.h"
#include "EscapeGameModeBase.h"
#include "Item.h"
#include "Components/SphereComponent.h"
#include "Character_Controller.generated.h"

// Forward Declarations
class AEscapeGameModeBase;

USTRUCT(BlueprintType)
struct FInventoryItem : public FTableRowBase {
	
	GENERATED_BODY()

public:

	FInventoryItem() {
		name = FText::FromString("Item");
		isVisible = false;
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName ItemID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class AItem> Item;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isVisible;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* image;

	bool operator==(const FInventoryItem& item) const {
		if (ItemID == item.ItemID) {
			return true;
		}
		else {
			return false;
		}
	}
};

UCLASS()
class ESCAPE_API ACharacter_Controller : public ACharacter
{
	GENERATED_BODY()

	AEscapeGameModeBase* GameMode;

public:
	// Sets default values for this character's properties
	ACharacter_Controller();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Items")
		void Collect();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
		void InventoryPlus();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
		void InventoryMinus();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Horizontal_Movement(float axis);

	void Vertical_Movement(float axis);

	UFUNCTION(BlueprintCallable, Category = "Utilities")
		void AddToInventory(FName id);

	UFUNCTION(BlueprintCallable, Category = "Utilities")
		void RemoveFromInventory();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
		void Holding();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		TArray<FInventoryItem> inventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int InventoryI;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
		class USphereComponent* collectionRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FInventoryItem hold;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FInventoryItem empty;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FInventoryItem> PickupableObjects;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Holding Items")
		TArray<AActor*> HoldObjects;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool JustPickedUp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool JustRemoved;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool BlackTriggerBox;


	FORCEINLINE class USphereComponent* GetCollectionRange() const { return collectionRange; }
};
