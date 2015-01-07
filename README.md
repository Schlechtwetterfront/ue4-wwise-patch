Paste this into your UE4 engine directory and then recompile the engine.





Welcome to the Wwise Unreal Engine 4 integration!
=================================================

This is the source code page for the Wwise integration in Unreal Engine 4.

You can build the editor for Windows, and compile games for Windows, Playstation 4 and Xbox One.

If you need any help, please refer to the `Wwise_UE4_Integration.chm` file in the repository. You can also visit the [Q&A section](https://www.audiokinetic.com/qa/) on the Audiokinetic website.



Source releases
---------------

This integration is compatible with Unreal Engine 4.6 and is based on Wwise 2014.1.1. You can download the latest Wwise version [here](http://www.audiokinetic.com/downloads/).

If you wish to compile against Wwise 2013.2.x, simply remove the following line in `<UE4_ROOT>/Engine/Source/ThirdParty/Audiokinetic/Audiokinetic.Build.cs`: 

	AddWwiseLib(Target, "AkSynthOne", akPlatformLibPath);



Installation
------------

1. Follow steps 1 to 5 from the "Getting up and running" section of the Unreal Engine [README\_UE\_Original.md](https://github.com/audiokinetic/WwiseUE4Integration/blob/4.6/README_UE_Original.md) file to setup Unreal Engine 4 on your computer.
1. Install Wwise.

    **NOTE**: If you install Wwise in a custom location on your hard disk, make sure to update the "WwiseCommandLinePath" in the "UE4/Engine/Config/BaseEditor.ini" file. The correct path to the Wwise application is required in order to generate the Wwise SoundBanks from the Unreal Editor. For more information, please refer to the "Wwise Unreal Integration > Using the Integration > Initial Setup" section located in `Wwise_UE4_Integration.chm` file.
1. Copy the necessary Wwise SDK files from your Wwise installation to your Unreal Engine 4 working directory:
	* Copy `<Wwise installation directory>\SDK\include` to `<Unreal Engine 4 root folder>\Source\ThirdParty\Audiokinetic\include`
	* Copy `<Wwise installation directory>\SDK\samples\SoundEngine` to `<Unreal Engine 4 root folder>\Source\ThirdParty\Audiokinetic\samples\SoundEngine`
	* Copy the libraries for your platform:
		* Windows
			* Copy `<Wwise installation directory>\SDK\Win32_vc120\*` to `<Unreal Engine 4 root folder>\Source\ThirdParty\Audiokinetic\Win32_vc120`
			* Copy `<Wwise installation directory>\SDK\x64_vc120\*` to `<Unreal Engine 4 root folder>\Source\ThirdParty\Audiokinetic\x64_vc120`
		* Playstation 4:
			* Copy `<Wwise installation directory>\SDK\PS4\*` to `<Unreal Engine 4 root folder>\Source\ThirdParty\Audiokinetic\PS4`
		* Xbox One:
			* Copy `<Wwise installation directory>\SDK\XboxOne_vc110\*` to `<Unreal Engine 4 root folder>\Source\ThirdParty\Audiokinetic\XboxOne_vc110`
1. Follow the instructions found in the [README\_UE\_Original.md](https://github.com/audiokinetic/WwiseUE4Integration/blob/4.6/README_UE_Original.md) file to generate the project files & compile the editor.
1. You are now ready to use Wwise in your Unreal Engine 4 game!


Example Game
------------

This integration showcases its fundamental concepts in a bundled demo game. For more information, please refer to the "Using the integration > Sample Game" section located in the `Wwise_UE4_Integration.chm` file.
