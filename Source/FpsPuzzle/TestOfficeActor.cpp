// Fill out your copyright notice in the Description page of Project Settings.


#include "TestOfficeActor.h"

ATestOfficeActor::ATestOfficeActor()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TestOfficeMesh"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_TARGET(TEXT("StaticMesh'/Game/OfficePack/StaticMesh/SM_Chair06.SM_Chair06'"));

	if (SM_TARGET.Succeeded())
	{
		Cast<UStaticMeshComponent>(Mesh)->SetStaticMesh(SM_TARGET.Object);
	}

	Mesh->SetCollisionProfileName(TEXT("ShotAttackable"));
	Mesh->SetSimulatePhysics(true);

	RootComponent = Mesh;

	SetActorScale3D(FVector(2.0f, 2.0f, 2.0f));
}