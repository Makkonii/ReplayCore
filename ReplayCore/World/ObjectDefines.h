#ifndef __OBJECT_DEFINES_H
#define __OBJECT_DEFINES_H

#include "../Defines/Common.h"

#define DEFAULT_VISIBILITY_DISTANCE 100.0f             // default visible distance on continents, used to be 90 yards
#define DEFAULT_VISIBILITY_INSTANCE 170.0f             // default visible distance in instances, used to be 120 yards
#define DEFAULT_VISIBILITY_BG       533.0f             // default visible distance in BG, used to be 180 yards
#define DEFAULT_VISIBILITY_MODIFIER 0.0f               // default visibility modifier on some units that should be seen beyond normal visibility distances
#define DEFAULT_CREATURE_SUMMON_LIMIT  100             // default maximum number of creatures an object can have summoned at once

#define VISIBILITY_DISTANCE_GIGANTIC    400.0f
#define VISIBILITY_DISTANCE_LARGE       200.0f
#define VISIBILITY_DISTANCE_NORMAL      100.0f
#define VISIBILITY_DISTANCE_SMALL       50.0f
#define VISIBILITY_DISTANCE_TINY        25.0f

#define DEFAULT_WORLD_OBJECT_SIZE   0.388999998569489f      // currently used (correctly?) for any non Unit world objects. This is actually the bounding_radius, like player/creature from creature_model_data
#define DEFAULT_OBJECT_SCALE        1.0f                    // player/item scale as default, npc/go from database, pets from dbc
#define DEFAULT_GNOME_SCALE         1.15f
#define DEFAULT_TAUREN_MALE_SCALE   1.35f                   // Tauren Male Player Scale by default
#define DEFAULT_TAUREN_FEMALE_SCALE 1.25f                   // Tauren Female Player Scale by default

struct Position
{
    Position() = default;
    Position(float position_x, float position_y, float position_z, float orientation) : x(position_x), y(position_y), z(position_z), o(orientation) {}
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
    float o = 0.0f;
    bool operator!=(Position const& other) const
    {
        return !(x == other.x && y == other.y && z == other.z && o == other.o);
    }
};

struct WorldLocation : public Position
{
    uint16 mapId = 0;
    explicit WorldLocation(uint16 mapId_ = 0, float x_ = 0, float y_ = 0, float z_ = 0, float o_ = 0)
        : Position(x_, y_, z_, o_), mapId(mapId_) {}
    WorldLocation(WorldLocation const& loc)
        : Position(loc.x, loc.y, loc.z, loc.o), mapId(loc.mapId) {}
    Position ToPosition() const { return Position(x, y, z, o); }
};

#endif