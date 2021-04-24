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

		PlayerSpeed = Player->PlayerSpeed;
		IsAir = Player->GetMovementComponent()->IsFalling();
		DirForward = Player->GetInputDirForward();
		DirRight = Player->GetInputDirRight();;
		AimDirForward = Player->GetAimDirForward();
		AimDirRight = Player->GetAimDirRight();
		Upper_Pitch = Player->GetUpper_Pitch();
		Upper_Yaw = Player->GetUpper_Yaw();
		Upper_Yaw2 = Player->GetUpper_Yaw2();
		StateUpperNClass = Player->StateUpperNClass;
		StateDownNClass = Player->StateDownNClass;
		StateUpperBClass = Player ->StateUpperBClass;
		StateDownBClass = Player->StateDownBClass;
	}
}
