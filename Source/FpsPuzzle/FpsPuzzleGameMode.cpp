// Fill out your copyright notice in the Description page of Project Settings.


#include "FpsPuzzleGameMode.h"
#include "FpsPuzzleCharacter.h"
#include "FpsPuzzlePlayerController.h"

AFpsPuzzleGameMode::AFpsPuzzleGameMode()
{
	DefaultPawnClass = AFpsPuzzleCharacter::StaticClass();
	PlayerControllerClass = AFpsPuzzlePlayerController::StaticClass();
}
