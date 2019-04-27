//header file for the hardware portion
class HW{
};

class MMU: public HW{
}

class PageFault: public MMU{
};
class Word: public HW{
};

class Adr: public Word{
};

class BS:public HW{
};

class RAM: public HW{
};

class status: public RAM{
};
