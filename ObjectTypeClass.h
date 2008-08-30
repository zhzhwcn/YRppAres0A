/*
	ObjectTypes are initialized by INI files.
*/

#ifndef OBJTYPE_H
#define OBJTYPE_H

#include <AbstractTypeClass.h>
#include <FileSystem.h>

//forward declarations
class TechnoTypeClass;
class HouseTypeClass;
class ObjectClass;
class BuildingTypeClass;

class ObjectTypeClass : public AbstractTypeClass
{
public:
	//IPersistStream
	virtual HRESULT _stdcall Load(IStream* pStm)
		{ PUSH_VAR32(pStm); PUSH_VAR32(this); CALL(0x5F9720); }

	virtual HRESULT _stdcall Save(IStream* pStm, BOOL fClearDirty)
		{ PUSH_VAR32(fClearDirty); PUSH_VAR32(pStm); PUSH_VAR32(this); CALL(0x5F9950); }

	virtual HRESULT _stdcall GetSizeMax(ULARGE_INTEGER* pcbSize)
		{ PUSH_VAR32(pcbSize); PUSH_VAR32(this); CALL(0x5F9970); }

	//Destructor
	virtual ~ObjectTypeClass()
		{ THISCALL(0x5F7400); }

	//AbstractTypeClass
	virtual bool LoadFromINI(CCINIClass* pINI)
		{ PUSH_VAR32(pINI); THISCALL(0x5F92D0); }

	//ObjectTypeClass
	virtual CoordStruct* vt_entry_6C(CoordStruct* pDest, CoordStruct* pSrc)
		{ PUSH_VAR32(pSrc); PUSH_VAR32(pDest); THISCALL(0x41CF80); }

	virtual DWORD GetOwners()
		{ return 0xFFFFFFFF; }

	virtual int GetPipMax()
		{ return 0; }

	virtual void vt_entry_78(DWORD dwUnk)
		{ }

	virtual void vt_entry_7C(DWORD dwUnk)
		{ }

	virtual bool SpawnAtMapCoords(CellStruct* pMapCoords, HouseClass* pOwner) = 0;

	virtual int GetActualCost(HouseTypeClass* pCountry)
		{ return 0; }

	virtual int GetBuildSpeed()
		{ return 0; }

	virtual ObjectClass* CreateObject(HouseClass* pOwner) = 0;

	virtual void vt_entry_90(DWORD dwUnk)
		{ }

	virtual BuildingTypeClass* GetFactoryType(bool OverridePrereqs, bool OverridePower, bool OverrideBuildLimit, 
		HouseClass *House)
		{ PUSH_VAR32(House); PUSH_VAR8(OverrideBuildLimit); PUSH_VAR8(OverridePower); PUSH_VAR8(OverridePrereqs);
		  THISCALL(0x5F7900); }

	virtual SHPStruct* GetCameo()
		{ return NULL; }

	virtual SHPStruct* GetImage()
		{ return Image; }

	//Constructor
	ObjectTypeClass(const char* pID):AbstractTypeClass(false)
		{ PUSH_VAR32(pID); THISCALL(0x5F7090); }

protected:
	ObjectTypeClass() { }
	ObjectTypeClass(bool X):AbstractTypeClass(X) { }; //trick to disable base class construction!

	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================
	PROPERTY_STRUCT(ColorStruct,   RadialColor);
	PROPERTY(BYTE,          unused_9B);
	PROPERTY(int,           Armor);
	PROPERTY(int,           Strength);
	PROPERTY(SHPStruct*,    Image);
	PROPERTY(bool,          IsImageAllocated);
	PROPERTY(bool,          unused_A9);
	PROPERTY(bool,          unused_AA);
	PROPERTY(bool,          unused_AB);
	PROPERTY(SHPStruct*,    AlphaImage);
	PROPERTY_STRUCT(VoxelStruct,   MainVoxel);
	PROPERTY_STRUCT(VoxelStruct,   TurretVoxel); //also used for WO voxels
	PROPERTY_STRUCT(VoxelStruct,   BarrelVoxel);

	PROPERTY_STRUCT_ARRAY(VoxelStruct, ChargerTurrets, 0x12);
	PROPERTY_STRUCT_ARRAY(VoxelStruct, ChargerBarrels, 0x12);

	PROPERTY(bool,          NoSpawnAlt);
	PROPERTY(BYTE,          unused_1E9);
	PROPERTY(BYTE,          unused_1EA);
	PROPERTY(BYTE,          unused_1EB);
	PROPERTY(int,           MaxDimension);
	PROPERTY(int,           CrushSound); //index
	PROPERTY(int,           AmbientSound); //index

	PROPERTY_STRING(ImageFile, 0x19);

	PROPERTY(bool,           AlternateActicArt);
	PROPERTY(bool,           ArcticArtInUse); //not read from ini

	PROPERTY_STRING(AlphaImageFile, 0x19);

	PROPERTY(bool,           Theater);
	PROPERTY(bool,           Crushable);
	PROPERTY(bool,           Bombable);
	PROPERTY(bool,           RadarInvisible);
	PROPERTY(bool,           Selectable);
	PROPERTY(bool,           LegalTarget);
	PROPERTY(bool,           Insignificant);
	PROPERTY(bool,           Immune);
	PROPERTY(bool,           Voxel);
	PROPERTY(bool,           NewTheater);
	PROPERTY(bool,           HasRadialIndicator);
	PROPERTY(bool,           IgnoresFirestorm);
	PROPERTY(bool,           UseLineTrail);
	PROPERTY_STRUCT(ColorStruct,    LineTrailColor);
	PROPERTY(BYTE,           unused_23E);
	PROPERTY(BYTE,           unused_23F);
	PROPERTY(int,            LineTrailColorDecrement);

	PROTECTED_PROPERTY(BYTE, unknown_244[0x50]); //These don't even seem to be of any use...
};

#endif