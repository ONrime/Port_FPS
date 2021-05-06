// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerBody_AnimInstance.h"
#include "Port_FPS/Character/Player/Player_CharacterBase.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/Controller.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/RotationMatrix.h"
#include "Port_FPS/Character/Player/MultiPlayer/MultiPlayer_CharacterBase.h"

UPlayerBody_AnimInstance::UPlayerBody_AnimInstance() {

}

void UPlayerBody_AnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner();
	if (::IsValid(Pawn)) {
		auto Player = Cast<APlayer_CharacterBase>(Pawn);
		FVector PlayerVelocity = Player->GetVelocity();
		FRotator PlayerRotator = Player->GetActorRotation();
		PlayerVelocity.Normalize();

		FMatrix RotMatrix = FRotationMatrix(Player->GetActorRotation());
		FVector ForwardVector = RotMatrix.GetScaledAxis(EAxis::X);
		FVector RightVector = RotMatrix.GetScaledAxis(EAxis::Y);
		FVector NormalizedVel = PlayerVelocity.GetSafeNormal2D();

		DirForward = FVector::DotProduct(ForwardVector, NormalizedVel);
		DirRight = FVector::DotProduct(RightVector, NormalizedVel);

		//UE_LOG(LogTemp, Warning, TEXT("ForwardCosAngle.Xxx: %f"), ForwardCosAngle);
		//UE_LOG(LogTemp, Warning, TEXT("Direction.Yyy: %f"), RightCosAngle);

		PlayerSpeed = Player->GetVelocity().Size();
		IsAir = Player->GetMovementComponent()->IsFalling();
		AimDirForward = Player->GetAimDirForward();
		AimDirRight = Player->GetAimDirRight();

		auto PlayerM = Cast<AMultiPlayer_CharacterBase>(Pawn);
		Upper_Pitch = Player->GetUpper_Pitch();
		Upper_Yaw = Player->GetUpper_Yaw();
		Upper_Yaw2 = Player->GetUpper_Yaw2();

		StateUpperNClass = Player->StateUpperNClass;
		StateDownNClass = Player->StateDownNClass;
		StateUpperBClass = Player ->StateUpperBClass;
		StateDownBClass = Player->StateDownBClass;
	}
}
