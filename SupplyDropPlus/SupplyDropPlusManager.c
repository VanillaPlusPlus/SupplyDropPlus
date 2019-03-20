///////////////////////////////////////////////
//Airdrop System       		             //
//Author: GravityWolf 			     //
//Github: github.com/gravitywolfnotamused    //
///////////////////////////////////////////////

#include "$CurrentDir:\\mpmissions\\dayzOffline.chernarusplus\\SupplyDropPlus\\SupplyDropPlusPlane.c"
#include "$CurrentDir:\\mpmissions\\dayzOffline.chernarusplus\\SupplyDropPlus\\SupplyDropPlusConfig.c"

class SupplyDropPlusManager
{
	private float timeSnapshot;
	private float roundedSnapShot;
	private float lifeTimeClock;
		
	private ref SupplyPlanes planes;
	private ref Supplies supplies;
	private ref SupplyDropPlusConfig config;

	void SupplyDropPlusManager()
	{	
		planes = new SupplyPlanes;
		supplies = new Supplies;

		config = new SupplyDropPlusConfig();
		config.load();
	}
	
	void Init(){
		Print("SupplyDrop::Init Plugin Initialized.");
	}
	
	void onUpdate(float timeslice){		
		timeSnapshot += timeslice;

		if(supplies.Count() != 0){		
			lifeTimeClock += timeslice;
		}
		
		if(timeSnapshot >= config.getDropTime()){
			timeSnapshot = 0;
			roundedSnapShot = 0;

			if(planes.Count() != config.getMaxDrops()){
				vector location = getStartingPosition();
				
				if(config.canSendMessage()){
					GetGame().ChatPlayer("A supply plane was spotted at " + location.ToString());
				}

				planes.Insert(new SupplyDropPlusPlane(location, config.chooseDropLocation()));
			}
		}

		if(planes.Count() > 0){
			foreach(SupplyDropPlusPlane plane : planes){
				if(Math.Round(plane.getPosition()[0]) >= Math.Round(plane.getDropPosition()[0]) - 25 && Math.Round(plane.getPosition()[0]) <= Math.Round(plane.getDropPosition()[0]) + 25){
					if(Math.Round(plane.getPosition()[2]) >= Math.Round(plane.getDropPosition()[2]) - 25 && Math.Round(plane.getPosition()[2]) <= Math.Round(plane.getDropPosition()[2]) + 25){
						if(!plane.hasDroppedSupplies()){
							if(config.canSendMessage()){
								GetGame().ChatPlayer("Supplies were dropped at " + plane.getPosition());
							}
							
							supplies.Insert(new SupplyCratePlus(Vector(plane.getPosition()[0],plane.getPosition()[1] - 15,plane.getPosition()[2]), config.chooseLoot()));
							plane.setHasDroppedSupplies();
						}
					}
				}
				
				if((plane.getPosition()[0] < 1 || plane.getPosition()[2] < 1 || plane.getPosition()[0] > 15400 || plane.getPosition()[2] > 15400)){
					GetGame().ObjectDelete(plane.getObject());
					planes.RemoveItem(plane);			
					Print("Plane hit out of bounds, deleting.");
				}
				plane.move();
			}
		}

		if(supplies.Count() > 0){
			foreach(SupplyCratePlus supplyDrop : supplies){
				supplyDrop.setCurrentLifetime(timeslice);
				
				if(supplyDrop.getEndY() <= supplyDrop.getObject().GetPosition()[1] && supplyDrop.getObject().GetPosition()[1] != supplyDrop.getEndY()){
					supplyDrop.setPosition(supplyDrop.getEndYVector());
					supplyDrop.spawnFlares();
				}
				
				if(config.getDespawnTime() < supplyDrop.getLifeTime()){
					supplyDrop.despawnFlares();
					GetGame().ObjectDelete(supplyDrop.getObject());
					supplies.RemoveItem(supplyDrop);
					Print("Supply Create has lived it's life, it has been despawned.");
					continue;
				}
			}
		}
	}
	
	vector getStartingPosition(){
		vector starting = "0 0 1";
		starting[0] = Math.RandomFloat(0,15100);

		if(starting[0] >= 14400){
			starting[2] = Math.RandomFloat(0, 12200);
		}
		return starting;
	}
}
