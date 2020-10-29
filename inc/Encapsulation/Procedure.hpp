/*
 * Project Name = CCP_plazza_2019
 *
 * Author = magalie.vandenbriele | irama.chaouch | yoann.milanesio
 * Object = Kitchens class
 *
 * File creation = 06.05.20
 * Last modification = 06.05.20
 */

#ifndef __PROCEDURE__
#define __PROCEDURE__

class Procedure
{
    public:
        virtual int run();
        void stop();
    protected:
        unsigned int _id;
        bool _run;
};

#endif //__PROCEDURE__