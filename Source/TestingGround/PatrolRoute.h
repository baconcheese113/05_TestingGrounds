// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "PatrolRoute.generated.h"

/*
*	A "route card" to help AI choose their next waypoint.
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TESTINGGROUND_API UPatrolRoute : public UActorComponent
{
	GENERATED_BODY()

public:	

	TArray <AActor*> GetPatrolPoints() const;
	
	// Sets default values for this component's properties
	UPatrolRoute();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;


private:
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	TArray <AActor*> PatrolPoints; // TODO Make getter method
	
};
