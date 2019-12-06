// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "Abilities/Ability.h"
#include "AreaTimeSlowAbility.generated.h"


/**
 * 
 */
UCLASS()
class TOPDOWNARPG_API UAreaTimeSlowAbility : public UAbility
{
	GENERATED_BODY()
	
public:
	virtual void Activate(AActor* Source) override;

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AArea> AreaClass;
};
