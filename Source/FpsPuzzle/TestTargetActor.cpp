// Fill out your copyright notice in the Description page of Project Settings.


#include "TestTargetActor.h"

ATestTargetActor::ATestTargetActor()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TestTargetMesh"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_TARGET(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));

	if (SM_TARGET.Succeeded())
	{
		Cast<UStaticMeshComponent>(Mesh)->SetStaticMesh(SM_TARGET.Object);
	}

	Mesh->SetCollisionProfileName(TEXT("ShotAttackable"));
	Mesh->SetSimulatePhysics(true);

	RootComponent = Mesh;
}