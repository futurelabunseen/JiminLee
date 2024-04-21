// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "UNAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class PROEJCTUN_API UUNAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
	
protected:
	TObjectPtr<AGameplayAbilityTargetActor> CurrentActiveTargetActor;

public:
	TObjectPtr<AGameplayAbilityTargetActor> GetCurrentActiveTargetActor() { return CurrentActiveTargetActor; }
	void SetCurrentActiveTargetActor(TObjectPtr<AGameplayAbilityTargetActor> NewCurrentActiveTargetActor) { CurrentActiveTargetActor = NewCurrentActiveTargetActor; }
};