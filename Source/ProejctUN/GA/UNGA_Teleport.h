// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "UNGA_Teleport.generated.h"

/**
 * 
 */
UCLASS()
class PROEJCTUN_API UUNGA_Teleport : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	UUNGA_Teleport();

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData);
};