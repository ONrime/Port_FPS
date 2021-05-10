// Fill out your copyright notice in the Description page of Project Settings.


#include "Standing_PlayerDown_StateBase.h"
#include "Port_FPS/Character/Player/PlayerState/Crouch_PlayerDown_StateBase.h"
#include "GameFramework/PlayerInput.h"
#include "GameFramework/PlayerController.h"
#include "Port_FPS/Character/Player/MultiPlayer/MultiPlayer_CharacterBase.h"
#include "Net/UnrealNetwork.h"

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
	//UE_LOG(LogTemp, Warning, TEXT("UStanding_PlayerDown: Start"));
	PlayerBase->IsMove=true;
	PlayerBase->PlayerSpeed = 70.0f;

	CapsuleH = PlayerBase->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
	MeshLocZ = PlayerBase->GetMesh()->GetRelativeLocation().Z;

	PlayerBase->IsPlayerCameraTurn=true;

	if (PlayerBase->HasAuthority()) { // �÷��̾� ��ü ȸ�� (����)
		UE_LOG(LogTemp, Warning, TEXT("server_Update: %s UStanding_PlayerDown: Start"), *PlayerBase->GetName());
	}
	else { // (Ŭ���̾�Ʈ)
		if (PlayerBase->IsLocallyControlled()) {
			UE_LOG(LogTemp, Warning, TEXT("cla_Update: %s UStanding_PlayerDown: Start"), *PlayerBase->GetName());
		}
	}
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
	auto PlayerM = Cast<AMultiPlayer_CharacterBase>(PlayerBase);

	float Deltatime = GetWorld()->GetDeltaSeconds();
	float Pitch = PlayerBase->GetUpper_Pitch();
	float Yaw = PlayerBase->GetUpper_Yaw();

	if (!PlayerBase->HasAuthority() && PlayerBase->IsLocallyControlled()) {
		//UE_LOG(LogTemp, Warning, TEXT("cla_Update: %s UStanding_PlayerDown: TurnAtRate"), *PlayerBase->GetName());
	}

	if (PlayerBase->IsPlayerCameraTurn) {  //������ ���� ĳ���� ȸ�� ���� true=������ ���� �̵� false=���ϴ� ���� ��� ĳ���� ȸ�� ����
		PlayerBase->SpringArm->bUsePawnControlRotation = true;
		if (PlayerBase->GetVelocity().X > 0 || PlayerBase->GetVelocity().Y > 0) {  //�����϶�
			PlayerRotationYawSpeed = 20.0f;
		}
		else {  // �� �����϶�
			if (Pitch <= -70.0f && (Yaw >= 75.0f || Yaw <= -75.0f)) {  //�������� ���̵� �Ҷ�
				PlayerRotationYawSpeed = 5.0f;
			}
			else
				if (Pitch <= -70.0f && (Yaw <= 10.0f && Yaw >= -10.0f)) {  //�����ȿ��� ĳ���� �� �� �����̰� �Ҷ�
					PlayerRotationYawSpeed = 0.01f;
				}
				else
					if (Pitch > -70.0f) {  //������ ���� ĳ���� �� �̵� ��ų��
						PlayerRotationYawSpeed = 20.0f;
					}
		}
		if (PlayerBase->IsPlayerRotationYawSpeedSlow) {
			PlayerRotationYawSpeed = 0.01f;
		}
		
		PlayerRotationYaw = FMath::RInterpTo(PlayerBase->GetActorRotation(), PlayerBase->GetControlRotation(), GetWorld()->DeltaTimeSeconds, PlayerRotationYawSpeed).Yaw;
		PlayerM->PlayerRotationYaw = PlayerRotationYaw;
		PlayerM->PlayerRotationYawSpeed = PlayerRotationYawSpeed;
		
		PlayerBase->AddControllerYawInput(Rate * PlayerBase->BaseTurnRate * 0.008f);
	}
	else { // ī�޶� ������ ����
		PlayerBase->SpringArm->bUsePawnControlRotation = false;
	}


	// ī�޶� ȸ�� ȿ��
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

	// �÷��̾� ī�޶�
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
