//////////////////////////////////////////////
//Airdrop System 			   			 	//
//Author: GravityWolf 					 	//
//Github: github.com/gravitywolfnotamused	//
//////////////////////////////////////////////

typedef array<ref SupplyCratePlus> Supplies;

class SupplyCratePlus{
	private vector position;
	private bool hasFlares;

	private Object package;
	private EntityAI packageAI;

	private float currentLifeTime = 0;

	void SupplyCratePlus(vector position, ref array<string> pickedLoot){
		this.position = position;
		hasFlares = false;
		
		package = GetGame().CreateObject("SeaChest", position, false, true);
	 	package.SetDirection(package.GetDirection());
        	package.SetPosition(Vector(package.GetPosition()[0],700,package.GetPosition()[2]));

		if(Class.CastTo(packageAI, package)){
			foreach(string s : pickedLoot){
				packageAI.GetInventory().CreateInInventory(s);
			}
		}
		Print("Carepackage created at: " + position.ToString());
	}
	
	
	void spawnFlares(){
		if(hasFlares) return;
		
        	ref array<vector> positions = {"1 0 0", "-1 0 0", "0 0 1", "0 0 -1"};
        	string roadFlareClass = "Roadflare";
		Object obj;
		Roadflare flare;

		for(int x = 0; x < positions.Count(); x++){
		    obj = GetGame().CreateObject(roadFlareClass, package.GetPosition() + positions.Get(x), false, true);
		    flare = Roadflare.Cast(obj);
		    flare.SetModelState(RoadflareModelStates.UNCAPPED_IGNITED);
		    
		}
		hasFlares = true;
	}

	float getLifeTime(){
		return currentLifeTime;
	}
	void setCurrentLifetime(float Time){
		currentLifeTime += Time;
	}

	vector getPosition(){
		return position;
	}
	void setPosition(vector position){
		this.position = position;
		package.SetPosition(position);
	}

	Object getObject(){
		return package;
	}
	
	float getEndY(){
		return GetGame().SurfaceY(position[0], position[2]);
	}

	vector getEndYVector(){
		vector endVec = this.position;
		endVec[1] = getEndY();
		return endVec;
	}
}
