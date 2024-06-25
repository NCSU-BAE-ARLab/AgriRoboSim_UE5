// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ROSIntegration/Classes/ROSIntegrationGameInstance.h"
#include "ROSIntegration/Classes/RI/Topic.h"
#include "Components/ActorComponent.h"
#include "ROS2NodeComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AGRIROBOSIM_API UROS2NodeComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FString TopicPrefix;
	// Sets default values for this component's properties
	UROS2NodeComponent();
	UPROPERTY()
	UROSIntegrationGameInstance* rosinst;
	template<typename T>
	static void R2S_TArray_Helper(TArray<T> ROS, TArray<T>* Sim);
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
private:
	
	
	
	UPROPERTY()
	UTopic* Sim2ROS_Bool_Topic;
	UPROPERTY()
	UTopic* ROS2Sim_Bool_Topic;
	
	std::function<void(TSharedPtr<FROSBaseMsg>)> Bool_SubscribeCallback;
	
};

template <typename T>
void UROS2NodeComponent::R2S_TArray_Helper(TArray<T> ROS, TArray<T>* Sim)
{
	if (Sim->Num() < ROS.Num())
	{
		Sim->Reserve(ROS.Num());
	}
	for (int i = 0; i < ROS.Num(); i++)
	{
		if (i < Sim->Num())
		{
			(*Sim)[i] = ROS[i];
		} else
		{
			Sim->Add(ROS[i]);
		}
	}
	if (Sim->Num() > ROS.Num())
	{
		Sim->RemoveAt(ROS.Num(), Sim->Num() - ROS.Num());
	}
			
}