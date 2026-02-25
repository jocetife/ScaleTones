#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <wx/wx.h>

using namespace std;

enum class ScaleType{
    CM, DM, EM, FM, GM, AM, BM,     Cm, Dm, Em, Fm, Gm, Am, Bm,
    F_SHARP_m, G_FLAT_M, E_FLAT_m, D_SHARP_m, D_FLAT_M, B_FLAT_m, A_FLAT_M, E_FLAT_M, B_FLAT_M,

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

class MyFrame : public wxFrame {
public:
    MyFrame() : wxFrame(nullptr, wxID_ANY, "Validador de notas y acordes", wxDefaultPosition, wxSize(600, 250)) {
        wxPanel* panel = new wxPanel(this);   
        wxStaticText* text_tonality = new wxStaticText(panel, wxID_ANY, "Tonalidad", wxPoint(50, 50));
        wxChoice* tone_note = new wxChoice(panel, wxID_ANY, wxPoint(120, 50), wxSize(80,-1));
        wxChoice* type_scale = new wxChoice(panel, wxID_ANY, wxPoint(200, 50), wxSize(80, -1));
        wxStaticText* text_sequence = new wxStaticText(panel, wxID_ANY, "Secuencia", wxPoint(50, 80));
        wxTextCtrl* field_sequence = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(120, 80), wxSize(110, -1));
        wxButton* validate_sequence = new wxButton(panel, wxID_ANY, "Validar", wxPoint(230, 80), wxSize(50, -1));
    }
};

class MyApp : public wxApp {
public:
    bool OnInit() {
        MyFrame* frame = new MyFrame();
        frame->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(MyApp);



