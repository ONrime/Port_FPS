// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerBody_AnimInstance.h"
#include "Port_FPS/Character/Player/Player_CharacterBase.h"

UPlayerBody_AnimInstance::UPlayerBody_AnimInstance() {

}

void UPlayerBody_AnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner();
	if (::IsValid(Pawn)) {
		auto Player = Cast<APlayer_CharacterBase>(Pawn);

		
	}
}
