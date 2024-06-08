// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "EscapeGameModeBase.h"
#include "Character_Controller.h"

AEscapeGameModeBase::AEscapeGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
	PrimaryActorTick.bAllowTickOnDedicatedServer = false;

	DefaultPawnClass = ACharacter_Controller::StaticClass();
}