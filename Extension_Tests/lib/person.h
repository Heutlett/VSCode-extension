//
// Created by heutlett on 31/5/20.
//

#ifndef VSPTR_DYNAMICLIBRARY_PERSON_H __attribute__((visibility("default")));
#define VSPTR_DYNAMICLIBRARY_PERSON_H

class VSPTR_DYNAMICLIBRARY_PERSON_H person {
        public:

        person(int id, int otherId);
        ~person();
        static int size;

        static int envio();


        private:
        int id;
        int otherId;

};



#endif //VSPTR_DYNAMICLIBRARY_PERSON_H
