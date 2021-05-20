// Fill out your copyright notice in the Description page of Project Settings.


#include "InversionComponent.h"
#include "AttackableActor.h"

// Sets default values for this component's properties
UInversionComponent::UInversionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInversionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
	PrevTrans = FTransform();
}


// Called every frame
void UInversionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	AAttackableActor* Owner = Cast<AAttackableActor>(GetOwner());

	if (Owner)
	{
		
		if (Owner->GetIsInversed())
		{
			FTransform CurrentTrans;
			CurrentTrans = Owner->GetTransform();

			if (CurrentTrans.Equals(PrevTrans))
			{
				Owner->GetMesh()->SetSimulatePhysics(false);
				Owner->SetIsInversed(false);

				PrevTrans = CurrentTrans;

				return;
			}

			TransRecord.Add(CurrentTrans);
			PrevTrans = CurrentTrans;
		}
		else
		{
			Owner->GetMesh()->SetSimulatePhysics(true);

			if (TransRecord.Num())
			{
				FTransform Lerped;

				FTransform Trans = TransRecord.Pop();
				
				Lerped.SetLocation(FMath::Lerp(PrevTrans.GetLocation(), Trans.GetLocation(), 0.5));
				Lerped.SetRotation(FMath::Lerp(PrevTrans.GetRotation(), Trans.GetRotation(), 0.5));

				Owner->SetActorTransform(Lerped);

				PrevTrans = Trans;

				/*FTransform Trans = TransRecord.Pop();

				Owner->SetActorTransform(Trans);*/
			}
		}
	}
}

