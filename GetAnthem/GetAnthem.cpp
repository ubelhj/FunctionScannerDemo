#include "pch.h"
#include "GetAnthem.h"


BAKKESMOD_PLUGIN(GetAnthem, "write a plugin description here", plugin_version, PLUGINTYPE_FREEPLAY)

std::shared_ptr<CVarManagerWrapper> _globalCvarManager;

void GetAnthem::onLoad()
{
	_globalCvarManager = cvarManager;
	cvarManager->log("Plugin loaded!");

	
	gameWrapper->HookEventWithCallerPost<ProductWrapper>("Function TAGame.Product_TA.GetHashID", 
		[this](ProductWrapper caller, void * params, std::string eventName) {
			cvarManager->log(eventName);

			onGetHash(caller);
		});
}

void GetAnthem::onUnload()
{
}

void GetAnthem::onGetHash(ProductWrapper caller) {
	if (!caller) {
		cvarManager->log("Null product");
		return;
	}

	UnrealStringWrapper label = caller.GetLabel();

	if (!label) {
		return;
	}

	cvarManager->log("label: " + label.ToString());
	
	cvarManager->log("id: " + std::to_string(caller.GetID()));

	UnrealStringWrapper labelSlot = caller.GetDisplayLabelSlot();

	if (!labelSlot) {
		return;
	}

	cvarManager->log("label slot: " + labelSlot.ToString());

}