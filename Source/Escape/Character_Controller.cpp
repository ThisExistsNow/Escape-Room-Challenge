// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Character_Controller.h"
AEscapeGameModeBase* GameMode;

// Sets default values
ACharacter_Controller::ACharacter_Controller()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InventoryI = 0;
	//changed to "4"
	empty.ItemID = "4";

	collectionRange = CreateDefaultSubobject<USphereComponent>(TEXT("collectionRange"));
	RootComponent = collectionRange;
	collectionRange->SetSphereRadius(100.0f);
}

// Called when the game starts or when spawned
void ACharacter_Controller::BeginPlay()
{
	Super::BeginPlay();
	
	for (int i = 0; i < HoldObjects.Num(); i++) {
		if (HoldObjects[i]) {
			HoldObjects[i]->SetActorHiddenInGame(true);
		}
	}
}

// Called every frame
void ACharacter_Controller::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACharacter_Controller::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("MoveX", this, &ACharacter_Controller::Vertical_Movement);
	InputComponent->BindAxis("MoveY", this, &ACharacter_Controller::Horizontal_Movement);

	InputComponent->BindAxis("CameraSide", this, &ACharacter_Controller::AddControllerYawInput);
	InputComponent->BindAxis("CameraUp", this, &ACharacter_Controller::AddControllerPitchInput);

	InputComponent->BindAction("Interaction", IE_Pressed, this, &ACharacter_Controller::Collect);
	InputComponent->BindAction("InventoryPlus", IE_Pressed, this, &ACharacter_Controller::InventoryPlus);
	InputComponent->BindAction("InventoryMinus", IE_Pressed, this, &ACharacter_Controller::InventoryMinus);
}

void ACharacter_Controller::Horizontal_Movement(float axis) {
	if (axis) {
		AddMovementInput(GetActorRightVector(), axis);
	}
}

void ACharacter_Controller::Vertical_Movement(float axis) {
	if (axis) {
		AddMovementInput(GetActorForwardVector(), axis);
	}
}

void ACharacter_Controller::Collect() {
	
	TArray<AActor*> collectedItems;
	collectionRange->GetOverlappingActors(collectedItems);

	for (int i = 0; i < collectedItems.Num(); i++) {
		AItem* const testItem = Cast<AItem>(collectedItems[i]);
		if (testItem && testItem->GetActive()) {
			testItem->Touched();
			AddToInventory(testItem->ItemID);
			testItem->SetActive(false);
		}
	}
}

void ACharacter_Controller::InventoryPlus() {
	InventoryI += 1;
	if (InventoryI >= 5) {
		InventoryI = 0;
	}
	Holding();
}

void ACharacter_Controller::InventoryMinus() {
	InventoryI -= 1;
	if (InventoryI < 0) {
		InventoryI = 4;
	}
	Holding();
}

void ACharacter_Controller::AddToInventory(FName ID) {
	AEscapeGameModeBase* gameMode = Cast<AEscapeGameModeBase>(GetWorld()->GetAuthGameMode());
	UDataTable* itemTable = gameMode->GetItemsDB();

	if (gameMode) {
		if (itemTable) {
			FInventoryItem* itemAdded = itemTable->FindRow<FInventoryItem>(ID, "");
			if (itemAdded) {
				inventory.Add(*itemAdded);
				Holding();
			}
		}
	}
}

void ACharacter_Controller::RemoveFromInventory() {
	if (inventory.Num() > InventoryI) {
		inventory.RemoveAt(InventoryI);
		Holding();
	}
}

void ACharacter_Controller::Holding() {

	BlackTriggerBox = false;

	if (inventory.Num() > InventoryI) {
		hold = inventory[InventoryI];
		if (&hold) {
			FString holdValue = hold.ItemID.ToString();
			int holdI = FCString::Atoi(*holdValue);
			for (int i = 0; i < PickupableObjects.Num(); i++) {
				if (hold.ItemID == PickupableObjects[i].ItemID) {
					if (HoldObjects[holdI]) {
						if (holdI == 0) {
							BlackTriggerBox = true;
						}
						HoldObjects[holdI]->SetActorHiddenInGame(false);
					}
				}
				else {
					if (HoldObjects[i]) {
						HoldObjects[i]->SetActorHiddenInGame(true);
					}
				}
			}
		}
	}
	else {
		hold = empty;
	}

	if (hold == empty) {
		for (int i = 0; i < PickupableObjects.Num(); i++) {
			HoldObjects[i]->SetActorHiddenInGame(true);
		}
	}
}