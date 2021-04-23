// Fill out your copyright notice in the Description page of Project Settings.


#include "Standing_PlayerDown_StateBase.h"
#include "Port_FPS/Character/Player/PlayerState/Crouch_PlayerDown_StateBase.h"
#include "GameFramework/PlayerInput.h"
#include "GameFramework/PlayerController.h"

UStanding_PlayerDown_StateBase::UStanding_PlayerDown_StateBase()
{

}

UPlayerDown_StateBase* UStanding_PlayerDown_StateBase::HandleInput(APlayer_CharacterBase* PlayerBase)
{
	auto PlayerController = Cast<APlayerController>(PlayerBase->GetController());
	auto PlayerInput = Cast<UPlayerInput>(PlayerController->PlayerInput);
	TArray < FInputActionKeyMapping > ActionCrouch = PlayerInput->GetKeysForAction(TEXT("Crouch"));

	if (PlayerInput->IsPressed(ActionCrouch[0].Key)) {
		temp = NewObject<UCrouch_PlayerDown_StateBase>(this, UCrouch_PlayerDown_StateBase::StaticClass());
	}
	return temp;
}

void UStanding_PlayerDown_StateBase::StateStart(APlayer_CharacterBase* PlayerBase)
{
	UE_LOG(LogTemp, Warning, TEXT("UStanding_PlayerDown: Start"));
	PlayerBase->IsMove=true;
	PlayerBase->PlayerSpeed = 70.0f;

	CapsuleH = PlayerBase->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
	MeshLocZ = PlayerBase->GetMesh()->GetRelativeLocation().Z;

	PlayerBase->IsPlayerCameraTurn=true;
}

void UStanding_PlayerDown_StateBase::StateUpdate(APlayer_CharacterBase* PlayerBase)
{
	CapsuleH = FMath::FInterpTo(CapsuleH, 96.0f, GetWorld()->DeltaTimeSeconds, 5.0f);
	MeshLocZ = FMath::FInterpTo(MeshLocZ, -97.0f, GetWorld()->DeltaTimeSeconds, 5.0f);
	if (CapsuleH != 96.0f) { PlayerBase->GetCapsuleComponent()->SetCapsuleHalfHeight(CapsuleH, true); }
	if (MeshLocZ != -97.0f) { PlayerBase->GetMesh()->SetRelativeLocation(FVector(-20.0f, 0.0f, MeshLocZ)); }
}

void UStanding_PlayerDown_StateBase::StateEnd(APlayer_CharacterBase* PlayerBase)
{
}

UClass* UStanding_PlayerDown_StateBase::GetState()
{
	return UStanding_PlayerDown_StateBase::StaticClass();
}

void UStanding_PlayerDown_StateBase::TurnAtRate(APlayer_CharacterBase* PlayerBase, float Rate)
{
	float Deltatime = GetWorld()->GetDeltaSeconds();
	float Pitch = PlayerBase->GetUpper_Pitch();
	float Yaw = PlayerBase->GetUpper_Yaw();
	if (PlayerBase->IsPlayerCameraTurn) {  //시점에 따른 캐릭터 회전 결정 true=시점에 따른 이동 false=원하는 방향 대로 캐릭터 회전 결정
		PlayerBase->SpringArm->bUsePawnControlRotation = true;

		if (PlayerBase->GetVelocity().X > 0 || PlayerBase->GetVelocity().Y > 0) {  //움직일때
			PlayerRotationYawSpeed = 20.0f;
		}
		else {  // 안 움직일때
			if (Pitch <= -70.0f && (Yaw >= 75.0f || Yaw <= -75.0f)) {  //시점으로 각이동 할때
				PlayerRotationYawSpeed = 5.0f;
			}
			else
				if (Pitch <= -70.0f && (Yaw <= 10.0f && Yaw >= -10.0f)) {  //시점안에서 캐릭터 각 안 움직이게 할때
					PlayerRotationYawSpeed = 0.01f;
				}
				else
					if (Pitch > -70.0f) {  //시점에 따라 캐릭터 각 이동 시킬때
						PlayerRotationYawSpeed = 20.0f;
					}
		}
		if (PlayerBase->IsPlayerRotationYawSpeedSlow) {
			PlayerRotationYawSpeed = 0.01f;
		}

		/*if (PlayerBase->GetSDodgeMove()) {
			FRotator InterpToAngle = FMath::RInterpTo(FRotator(0.0f, SProneYaw, 0.0f), ((Player->GetControlRotation() - Player->GetProneRot()).GetNormalized()), Deltatime, 500.0f);
			SProneYaw = InterpToAngle.Yaw;
			PlayerBase->SetProneYaw(SProneYaw);
			PlayerRotationYawSpeed = 200.0f;
		}*/

		PlayerRotationYaw = FMath::RInterpTo(PlayerBase->GetActorRotation(), PlayerBase->Controller->GetControlRotation(), GetWorld()->DeltaTimeSeconds, PlayerRotationYawSpeed).Yaw;
		PlayerBase->SetActorRelativeRotation(FRotator(0.0f, PlayerRotationYaw, 0.0f));
		PlayerBase->AddControllerYawInput(Rate * PlayerBase->BaseTurnRate * GetWorld()->GetDeltaSeconds());
		PlayerBase->SpringArm->SetRelativeRotation(FRotator(0.0f, PlayerBase->Controller->GetControlRotation().Yaw, 0.0f));
		//UE_LOG(LogTemp, Warning, TEXT("PlayerRotationYaw: %f"), PlayerRotationYaw);
		//UE_LOG(LogTemp, Warning, TEXT("GetControlRotation: %f"), Player->Controller->GetControlRotation().Yaw);
	}
	else { // 카메라 움직임 끄기
		PlayerBase->SpringArm->bUsePawnControlRotation = false;
	}


	// 카메라 회전 효과
	float CameraChangeRoll = 0.0f;
	/*if (PlayerBase->IsCoverAim_L || Player->IsCoverAim_R) {
		if (Player->IsCoverAim_L) {
			CameraChangeRoll = FMath::GetMappedRangeValueClamped(FVector2D(-15.0f, 20.0f), FVector2D(0.0f, -30.0f), Player->CoverAngle_L);
		}
		if (Player->IsCoverAim_R) {
			CameraChangeRoll = FMath::GetMappedRangeValueClamped(FVector2D(-15.0f, 20.0f), FVector2D(0.0f, 30.0f), Player->CoverAngle_R);
		}
	}
	else { CameraChangeRoll = FMath::GetMappedRangeValueClamped(FVector2D(-1.0f, 1.0f), FVector2D(-0.8f, 0.8f), Rate); }*/
	CameraChangeRoll = FMath::GetMappedRangeValueClamped(FVector2D(-1.0f, 1.0f), FVector2D(-0.8f, 0.8f), Rate);
	PlayerBase->FollowCamera->SetRelativeRotation(FRotator(0.0f, 0.0f
		, FMath::FInterpTo(PlayerBase->FollowCamera->GetRelativeRotation().Roll, CameraChangeRoll, GetWorld()->GetDeltaSeconds(), 5.0f)));

	// 플레이어 카메라
	FVector HeadCameraLoc = FVector::ZeroVector;
	//float PelvisZ = PlayerBase->GetPelvisZ();
	HeadCameraLoc = PlayerBase->GetTransform().InverseTransformPosition(PlayerBase->GetMesh()->GetSocketLocation("HeadCamera"));
	PlayerBase->SetHeadCameraLoc(FVector(HeadCameraLoc.X, HeadCameraLoc.Y
		, FMath::FInterpTo(PlayerBase->GetHeadCameraLoc().Z, 50.0f, GetWorld()->GetDeltaSeconds(), 5.0f)));

}

bool UStanding_PlayerDown_StateBase::CheckLoc(FVector now, FVector target, float min)
{
	if ((now.X <= target.X + min && now.X >= target.X - min) && (now.Y <= target.Y + min && now.Y >= target.Y - min) && (now.Z <= target.Z + min && now.Z >= target.Z - min)) {
		return true;
	}
	return false;
}
