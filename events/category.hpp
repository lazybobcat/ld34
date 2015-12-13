#ifndef CATEGORY_H
#define CATEGORY_H

namespace Category
{
    enum Type
    {
        None            = 0,
        SoundEffect     = 1 << 0,
        ParticleSystem  = 1 << 1,
        Player          = 1 << 2,
        Crate           = 1 << 3,
        Wall            = 1 << 4,
        PointCounter    = 1 << 5,
        DoorTrigger     = 1 << 6,
        // ...
        //MixedCategory        = Category1 | Category2,

    };
}

#endif // CATEGORY_H
