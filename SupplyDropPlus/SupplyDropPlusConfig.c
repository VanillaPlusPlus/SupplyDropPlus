class SupplyDropPlusConfig
{
	private int DropTime;
	private int DespawnTime;
	private int MaxDrops;
	private int lootCount;

	private bool canSendMessage;

	private ref array<string> AirDropLoot;
	private ref array<vector> AirDropLocations;
	static const string SETTINGS_FILE = "$profile:\\SupplyDropConfig.json";


	void SupplyDropPlusConfig()
	{
		AirDropLoot = new ref array<string>;
		AirDropLocations = new ref array<vector>;
		DropTime = 60;
		lootCount = 5;
		DespawnTime = 60;
		MaxDrops = 10;
		canSendMessage = true;
	}
	
	void createDefaults()
	{
		ref array<string> loot = {
			"TTSKOPants",
			"TacticalBaconCan",
			"M4A1",
			"PlateCarrierComplete",
			"BakedBeansCan",
			"WaterBottle",
		};
		
		ref array<vector> locations = {
			"8400 0 10200",
			"9120 0 5415",
			"6800 0 9000",
			"6000 0 11500",
			"1550 0 6750",
			"3600 0 3600",
			"1200 0 3100",
		};
		
		int max = 10;
		int time = 600;
		int despawnTime = 600;
		int lootCount = 5;
		addData(max, time, despawnTime, loot, locations, lootCount);
	}

	void addData(int max, int time, int despawntime, ref array<string> loot, ref array<vector> locations, int lootCount){
		AirDropLoot = loot;
		AirDropLocations = locations;
		DropTime = time;
		DespawnTime = despawntime;
		MaxDrops = max;
		this.lootCount = lootCount;
	}

	void save(){
		JsonFileLoader<SupplyDropPlusConfig>.JsonSaveFile(SETTINGS_FILE, this);
	}

	void load(){
		if (FileExist(SETTINGS_FILE)) {
			JsonFileLoader<SupplyDropPlusConfig>.JsonLoadFile(SETTINGS_FILE, this);
		}
		else{
			Print("No Airdrop Config found, creating Airdrop json.");
			createDefaults();
			save();
		}
	}

	ref array<string> chooseLoot(){
		ref array<string> lootArray = new array<string>;
		for(int i = 0; i < lootCount; i++){
			lootArray.Insert(AirDropLoot.GetRandomElement());
		}

		return lootArray;
	}

	bool canSendMessage(){
		return canSendMessage;
	}

	int getDropTime()
	{
		return DropTime;
	}
	
	int getMaxDrops()
	{
		return MaxDrops;
	}

	int getDespawnTime()
	{
		return DespawnTime;
	}
	
	vector chooseDropLocation()
	{
		return AirDropLocations.GetRandomElement();
	}
}