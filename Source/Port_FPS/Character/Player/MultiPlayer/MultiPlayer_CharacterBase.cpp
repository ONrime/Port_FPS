// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiPlayer_CharacterBase.h"
#include "Port_FPS/Character/Player/PlayerState/PlayerStateBase.h"
#include "Port_FPS/Character/Player/PlayerState/Aim_PlayerUpper_StateBase.h"
#include "Port_FPS/Character/Player/PlayerState/Standing_PlayerDown_StateBase.h"
#include "Port_FPS/Character/Player/PlayerState/MultiPlayer_State/Prone_M_PlayerDown_StateBase.h"

AMultiPlayer_CharacterBase::AMultiPlayer_CharacterBase()
{
	BodyMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BODY"));
	BodyMesh->SetupAttachment(RootComponent);
	BodyMesh->SetRelativeLocation(FVector(-20.0f, 0.0f, -97.0f));
	BodyMesh->SetRelativeRotation(FRotator(0.0f, 270.0f, 0.0f));
	BodyMesh->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	BodyMesh->SetCollisionProfileName("CharacterMesh");
	
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>LEGBODY_SKELETALMESH(TEXT("SkeletalMesh'/Game/Mannequin/Character/Mesh/SK_Mannequin.SK_Mannequin'"));
	if (LEGBODY_SKELETALMESH.Succeeded()) { BodyMesh->SetSkeletalMesh(LEGBODY_SKELETALMESH.Object); }
	static ConstructorHelpers::FClassFinder<UAnimInstance>LEGBODY_ANIMBP(TEXT("AnimBlueprint'/Game/Player/Animation/Body/PlayerBody_AnimBP.PlayerBody_AnimBP_C'"));
	if (LEGBODY_ANIMBP.Succeeded()) { BodyMesh->SetAnimInstanceClass(LEGBODY_ANIMBP.Class); }
	
	SpringArm->SetRelativeScale3D(FVector(0.2f, 0.2f, 0.2f));
	//GetMesh()->bOnlyOwnerSee = true;

}

void AMultiPlayer_CharacterBase::BeginPlay()
{
	Super::BeginPlay();
	BodyMesh->SetOwnerNoSee(true);
	BodyMesh->SetCastShadow(true);
	BodyMesh->bCastHiddenShadow = true;
	GetMesh()->HideBoneByName(FName("spine_03"), PBO_None);
	GetMesh()->SetOnlyOwnerSee(true);
	GetMesh()->SetCastShadow(false);
	//SetStateDownN(NewObject<UProne_M_PlayerDown_StateBase>(this, UProne_M_PlayerDown_StateBase::StaticClass()));
	//GetStateDownN()->StateStart(this);
}

void AMultiPlayer_CharacterBase::TurnAtRate(float Rate)
{
	Super::TurnAtRate(Rate);
	GetStateDownN()->TurnAtRate(this, Rate);
}

void AMultiPlayer_CharacterBase::LookUpAtRate(float Rate)
{
	Super::LookUpAtRate(Rate);
	GetStateDownN()->LookUpAtRate(this, Rate);
}

void AMultiPlayer_CharacterBase::PlayerJump()
{
	Super::PlayerJump();
}

void AMultiPlayer_CharacterBase::MoveForward(float Value)
{
	Super::MoveForward(Value);
}

void AMultiPlayer_CharacterBase::MoveRight(float Value)
{
	Super::MoveRight(Value);
}

void AMultiPlayer_CharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMultiPlayer_CharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AMultiPlayer_CharacterBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}
