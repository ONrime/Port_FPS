// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"
#include "OnlineSubsystem.h"
#include "ServerMenu_UserWidget.generated.h"


/**
 * 
 */
UCLASS()
class PORT_FPS_API UServerMenu_UserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UServerMenu_UserWidget(const FObjectInitializer& ObjectInitializer);

	//virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerSettings", meta = (BindWidget))
	bool testb = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerSettings")
	bool testc = false;

	UFUNCTION(BlueprintCallable, meta = (BindWidget))
	void JoinServer();
	UFUNCTION(BlueprintCallable, meta = (BindWidget))
	void FindServer();

protected:

private:
	UPROPERTY()
	class UGameInfo_Instance* GameIns;

	
};
