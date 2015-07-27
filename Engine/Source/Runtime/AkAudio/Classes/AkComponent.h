// Copyright (c) 2006-2012 Audiokinetic Inc. / All Rights Reserved

/*=============================================================================
    AkComponent.h:
=============================================================================*/

#pragma once

#include "AkComponent.generated.h"

/*------------------------------------------------------------------------------------
    UAkComponent
------------------------------------------------------------------------------------*/
UCLASS(ClassGroup=Audiokinetic, BlueprintType, hidecategories=(Transform,Rendering,Mobility,LOD,Component,Activation), AutoExpandCategories=AkComponent, meta=(BlueprintSpawnableComponent))
class AKAUDIO_API UAkComponent: public USceneComponent
{
    GENERATED_UCLASS_BODY()

public:

    /** Stop sound when owner is destroyed? */
    UPROPERTY()
    bool StopWhenOwnerDestroyed;

    /**
     * Posts this component's AkAudioEvent to Wwise, using this component as the game object source
     *
     */
    UFUNCTION(BlueprintCallable, Category="Audiokinetic|AkComponent")
    void PostAssociatedAkEvent();
    
    /**
     * Posts an event to Wwise, using this component as the game object source
     *
     * @param AkEvent       The event to post
     */
    UFUNCTION(BlueprintCallable, Category="Audiokinetic|AkComponent")
    void PostAkEvent( class UAkAudioEvent * AkEvent );
    
    /**
     * Posts an event to Wwise using its name, using this component as the game object source
     *
     * @param AkEvent       The event to post
     */
    UFUNCTION(BlueprintCallable, Category="Audiokinetic|AkComponent")
    void PostAkEventByName( const FString& EventName );
    
    /**
     * Stops playback using this component as the game object to stop
     */
    UFUNCTION(BlueprintCallable, Category="Audiokinetic|AkComponent")
    void Stop();
    
    /**
     * Sets an RTPC value, using this component as the game object source
     *
     * @param RTPC          The name of the RTPC to set
     * @param Value         The value of the RTPC
     * @param InterpolationTimeMs - Duration during which the RTPC is interpolated towards Value (in ms)
     */
    UFUNCTION(BlueprintCallable, Category="Audiokinetic|AkComponent")
    void SetRTPCValue( FString RTPC, float Value, int32 InterpolationTimeMs );
    
    /**
     * Posts a trigger to wwise, using this component as the game object source
     *
     * @param Trigger       The name of the trigger
     */
    UFUNCTION(BlueprintCallable, Category="Audiokinetic|AkComponent")
    void PostTrigger( FString Trigger );
    
    /**
     * Sets a switch group in wwise, using this component as the game object source
     *
     * @param SwitchGroup   The name of the switch group
     * @param SwitchState   The new state of the switch
     */
    UFUNCTION(BlueprintCallable, Category="Audiokinetic|AkComponent")
    void SetSwitch( FString SwitchGroup, FString SwitchState );

    /**
     * Sets whether or not to stop sounds when the component's owner is destroyed
     *
     * @param bStopWhenOwnerDestroyed   Whether or not to stop sounds when the component's owner is destroyed
     */
    UFUNCTION(BlueprintCallable, Category="Audiokinetic|AkComponent")
    void SetStopWhenOwnerDestroyed( bool bStopWhenOwnerDestroyed );

    /**
     * Set a game object's active listeners
     *
     * @param in_uListenerMask  Bitmask representing the active listeners (LSB = Listener 0, set to 1 means active)
     */
    UFUNCTION(BlueprintCallable, Category="Audiokinetic|AkComponent")
    void SetActiveListeners( int32 in_uListenerMask );

    // Reverb volumes functions

    /**
     * Set UseReverbVolumes flag. Set value to true to use reverb volumes on this component.
     *
     * @param inUseReverbVolumes    Whether to use reverb volumes or not.
     */
    UFUNCTION(BlueprintCallable, Category="Audiokinetic|AkComponent")
    void UseReverbVolumes(bool inUseReverbVolumes);

    // Occlusion/obstruction functions

    /** Modifies the attenuation computations on this game object to simulate sounds with a a larger or smaller area of effect. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AkComponent")
    float AttenuationScalingFactor;

    /** Time interval between occlusion/obstruction checks. Set to 0 to disable occlusion on this component. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AkComponent")
    float OcclusionRefreshInterval;

    /**
     * Return the real attenuation radius for this component (AttenuationScalingFactor * AkAudioEvent->MaxAttenuationRadius)
     */
    UFUNCTION(BlueprintCallable, Category="Audiokinetic|AkComponent")
    float GetAttenuationRadius() const;

    /** Modifies the attenuation computations on this game object to simulate sounds with a a larger or smaller area of effect. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AkComponent")
    UAkAudioEvent* AkAudioEvent;


#if CPP

    /*------------------------------------------------------------------------------------
        UActorComponent interface.
    ------------------------------------------------------------------------------------*/
    /**
     * Called after component is registered
     */
    virtual void OnRegister();

    /**
     * Called after component is unregistered
     */
    virtual void OnUnregister();

    /**
     * Clean up
     */
    virtual void FinishDestroy();
	virtual void OnComponentDestroyed() override;

    /**
     * Clean up after error
     */
    virtual void ShutdownAfterError();

    virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

    // Begin USceneComponent Interface
    virtual void Activate(bool bReset=false) override;
    virtual void OnUpdateTransform(bool bSkipPhysicsMove) override;
    // End USceneComponent Interface

    /** Gets all AkReverbVolumes at the AkComponent's current location, and puts them in a list
     *
     * @param OutReverbVolumes      Array containing the found AkReverbVolumes
     * @param Loc                   The location of the AkComponent
     */
    void UpdateAkReverbVolumeList(FVector Loc);

	void CalculateOcclusionValues(bool CalledFromTick);


private:
    /**
     * Register the component with Wwise
     */
    void RegisterGameObject();

    /**
     * Unregister the component from Wwise
     */
    void UnregisterGameObject();

    void UpdateGameObjectPosition();

    // Reverb Volume features ---------------------------------------------------------------------

    /** Computes the increment to apply to a fading AkReverbVolume for a given time increment.
     *
     * @param DeltaTime     The given time increment since last fade computation
     * @param FadeRate      The rate at which the fade is applied (percentage of target value per second)
     * @param TargetValue   The targer control value at which the fading stops
     * @return              The increment to apply
     */
    FORCEINLINE float ComputeFadeIncrement(float DeltaTime, float FadeRate, float TargetValue) const
    {
        // Rate (%/s) * Delta (s) = % for given delta, apply to target.
        return (FadeRate * DeltaTime) * TargetValue;
    }

    /** Look if a new AkReverbVolume is in this component's CurrentAkReverbVolumes. */
    int32 FindNewAkReverbVolumeInCurrentlist(uint32 AuxBusId);


    /** Apply the current list of AkReverbVolumes 
     *
     * @param DeltaTime     The given time increment since last fade computation
     */
    void ApplyAkReverbVolumeList(float DeltaTime);

    struct AkReverbVolumeFadeControl
    {
        uint32 AuxBusId;
        float CurrentControlValue;
        float TargetControlValue;
        float FadeRate;
        bool bIsFadingOut;
        float Priority;
		bool bIsInteriorVolume;

        AkReverbVolumeFadeControl(uint32 InAuxBusId, float InCurrentControlValue, float InTargetControlValue, float InFadeRate, bool InbIsFadingOut, float InPriority, bool InbIsInteriorVolume) :
            AuxBusId(InAuxBusId),
            CurrentControlValue(InCurrentControlValue),
            TargetControlValue(InTargetControlValue),
            FadeRate(InFadeRate),
            bIsFadingOut(InbIsFadingOut),
            Priority(InPriority),
            bIsInteriorVolume(InbIsInteriorVolume)
            {}
    };

    /** Array of the active AkReverbVolumes at the AkComponent's location */
    TArray<AkReverbVolumeFadeControl> CurrentAkReverbVolumes;

    /** Whether to use reverb volumes or not */
    bool bUseReverbVolumes;

    // Occlusion/obstruction features -------------------------------------------------------------

    /** 
     * Determine if this component is occluded
     * 
     * @param DeltaTime     Time elasped since last function call.
     */
    void SetOcclusion(const float DeltaTime);

    /** Last time occlusion was refreshed */
    float LastOcclusionRefresh;

    struct FAkListenerOcclusion
    {
        float CurrentValue;
        float TargetValue;

        FAkListenerOcclusion( float in_TargetValue = 0.0f, float in_CurrentValue = 0.0f) :
            CurrentValue(in_CurrentValue),
            TargetValue(in_TargetValue){};
    };

    TArray< FAkListenerOcclusion > ListenerOcclusionInfo;

    static const float OCCLUSION_FADE_RATE;

#endif

#if WITH_EDITORONLY_DATA
    /** Utility function that updates which texture is displayed on the sprite dependent on the properties of the Audio Component. */
    void UpdateSpriteTexture();
#endif


};
