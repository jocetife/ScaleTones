#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

enum class ScaleType{
    CM,
    DM,
    EM,
    FM,
    GM,
    AM,
    BM,

    Cm,
    Dm,
    Em,
    Fm,
    Gm,
    Am,
    Bm,

    F_SHARP_m,
    G_FLAT_M,
    E_FLAT_m,
    D_SHARP_m,
    D_FLAT_M,
    B_FLAT_m,
    A_FLAT_M,
    E_FLAT_M,
    B_FLAT_M,

    UNKNOWN
};

class Scale {
public:
    ScaleType parseScale (const string& tone){
        static unordered_map<string, ScaleType> map = {
            {"CM", ScaleType::CM}
        };
        auto it = map.find(tone); //auto, infiera el tipo de dato (iterador)
        if (it != map.end())
            return it->second;
        return ScaleType::UNKNOWN;
    }
    vector<string> scalesDetector(ScaleType scale){
        switch(scale){
            case ScaleType::CM:
            case ScaleType::Am:
                return {"C","D","E","F","G","A","B"};
            default:
                cout << "No existe esa tonalidad" << endl;
                return {};
        }
    }
};

int main(){
    
    cout << "What scale do you want to show? " << endl;
    string tone;
    getline(cin, tone);
    //cin.getline(tone, 20); //acepta espacios
    Scale scale1;
    vector<string> notas = scale1.scalesDetector(scale1.parseScale(tone));
    for(const string& n : notas){
        cout << n << " ";
    }
    return 0;
}

