//header file for the hardware portion
class HW{
};

class MMU: public HW{ //Memory Management Unit
}

class PageFault: public MMU{ 
};
class Word: public HW{
};

class Adr: public Word{ //Address
};

class BS:public HW{ //Backing Store
};

class RAM: public HW{
};

class status: public RAM{
};
