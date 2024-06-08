// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character_Controller.h"
#include "GameFramework/Actor.h"
#include "Poster.h"
#include "Engine/TriggerBox.h"
#include "BlackLightTriggerBox.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPE_API ABlackLightTriggerBox : public ATriggerBox
{
	GENERATED_BODY()
	
protected:
	
	virtual void BeginPlay() override;

public:

	ABlackLightTriggerBox();

	UFUNCTION(BlueprintCallable, Category = "Overlap")
		void OverPoster(class AActor* OverLappedActor, class AActor* OtherActor);

	UFUNCTION(BlueprintCallable, Category = "Overlap")
		void LeftPoster(class AActor* OverLappedActor, class AActor* OtherActor);

};
