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

		if (Player->HasAuthority()) {
			//로컬 붙이기?
			//FRotator InterpToAngle_Pitch = FMath::RInterpTo(FRotator(Upper_Pitch, 0.0f, 0.0f), ((Player->GetControlRotation() - Player->GetActorRotation()).GetNormalized()), GetWorld()->DeltaTimeSeconds, 500.0f);
			//Upper_Pitch = FMath::ClampAngle(InterpToAngle_Pitch.Pitch, -90.0f, 90.0f);
			auto PlayerM = Cast<AMultiPlayer_CharacterBase>(Pawn);
			//Upper_Pitch = Player->GetUpper_Pitch();
			//FRotator InterpToAngle_Yaw = FMath::RInterpTo(FRotator(0.0f, Upper_Yaw, 0.0f), ((Player->GetControlRotation() - Player->GetActorRotation()).GetNormalized()), GetWorld()->DeltaTimeSeconds, 500.0f);
			//Upper_Yaw = FMath::ClampAngle(InterpToAngle_Yaw.Yaw, -90.0f, 90.0f);
			//Upper_Yaw = Player->GetUpper_Yaw();
			//Upper_Yaw2 = Player->GetUpper_Yaw2();
			//Upper_Yaw = Player->GetUpper_Yaw();
		}

		Upper_Pitch = Player->GetUpper_Pitch();
		Upper_Yaw = Player->GetUpper_Yaw();
		Upper_Yaw2 = Player->GetUpper_Yaw2();

		StateUpperNClass = Player->StateUpperNClass;
		StateDownNClass = Player->StateDownNClass;
		StateUpperBClass = Player ->StateUpperBClass;
		StateDownBClass = Player->StateDownBClass;
	}
}

/*void UPlayerBody_AnimInstance::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UPlayerBody_AnimInstance, Upper_Yaw);
	DOREPLIFETIME(UPlayerBody_AnimInstance, Upper_Pitch);
}*/
