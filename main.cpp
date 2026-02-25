#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <wx/wx.h>
#include <wx/dcbuffer.h>
#include <wx/tglbtn.h>

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

/*class MyFrame : public wxFrame {
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
};*/
class LeftPanel : public wxPanel{
public:
    LeftPanel(wxWindow* parent) : wxPanel(parent){
        wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

        wxStaticText* text_tonality = new wxStaticText(this, wxID_ANY, "Tonalidad");
        wxChoice* tone_note = new wxChoice(this, wxID_ANY);
        wxChoice* type_scale = new wxChoice(this, wxID_ANY);

        wxStaticText* text_sequence = new wxStaticText(this, wxID_ANY, "Secuencia");
        wxTextCtrl* field_sequence = new wxTextCtrl(this, wxID_ANY);
        wxButton* validate_sequence = new wxButton(this, wxID_ANY, "Validar");

        sizer->Add(text_tonality, 0, wxALL, 5);
        sizer->Add(tone_note, 0, wxALL, 5);
        sizer->Add(type_scale, 0, wxALL, 5);
        sizer->Add(text_sequence, 0, wxALL, 5);
        sizer->Add(field_sequence, 0, wxALL | wxEXPAND, 5);
        sizer->Add(validate_sequence, 0, wxALL | wxCENTER, 5);

        this->SetSizer(sizer);
    }
};

class PianoDraw : public wxPanel {
public:
    PianoDraw(wxWindow* parent)
        : wxPanel(parent), timer(this)
    {
        SetBackgroundStyle(wxBG_STYLE_PAINT);

        Bind(wxEVT_PAINT, &PianoDraw::OnPaint, this);
        Bind(wxEVT_TIMER, &PianoDraw::OnTimer, this);
        Bind(wxEVT_SIZE, &PianoDraw::OnResize, this);

        timer.Start(16); // ~60 FPS (mucho más estable que 1ms)
    }

private:
    wxTimer timer;

    void OnTimer(wxTimerEvent&) {
        Refresh();  // Fuerza redibujado constante
    }

    void OnResize(wxSizeEvent& event) {
        Refresh();
        event.Skip();
    }

    void OnPaint(wxPaintEvent&) {
        wxAutoBufferedPaintDC dc(this);

        wxSize size = GetClientSize();
        if (size.x <= 0 || size.y <= 0)
            return;

        double totalWidth  = size.x;
        double totalHeight = size.y;

        double keyWidth  = totalWidth / 8.0;
        double keyHeight = totalHeight;

        dc.SetPen(*wxBLACK_PEN);

        //Teclas blancas
        for (int i = 0; i < 8; ++i) {
            double x1 = i * keyWidth;
            double x2 = (i + 1) * keyWidth;

            int x = static_cast<int>(x1);
            int w = static_cast<int>(x2 - x1);

            dc.SetBrush(*wxWHITE_BRUSH);
            dc.DrawRectangle(x, 0, w, static_cast<int>(keyHeight));
        }

        //Teclas negras
        for (int i = 0; i < 7; ++i) {
            if (i != 2 && i != 6) {

                double blackWidth  = keyWidth * 0.5;
                double blackHeight = keyHeight * 0.6;

                double center = (i + 1) * keyWidth;
                double x = center - blackWidth / 2.0;

                dc.SetBrush(*wxBLACK_BRUSH);
                dc.DrawRectangle(static_cast<int>(x), 0, static_cast<int>(blackWidth), static_cast<int>(blackHeight));
            }
        }
    }
};

class PianoControls : public wxPanel{
public:
    PianoControls(wxWindow* parent) : wxPanel(parent){
        wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);

        wxToggleButton* show_notes = new wxToggleButton(this, wxID_ANY, "Notas");
        wxToggleButton* show_chords = new wxToggleButton(this, wxID_ANY, "Acordes");

        sizer->Add(show_notes, 1, wxALL, 5);
        sizer->Add(show_chords, 1, wxALL, 5);

        this->SetSizer(sizer);
    }
};

class PianoPanel : public wxPanel{
public:
    PianoPanel(wxWindow* parent) : wxPanel(parent){
        wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

        PianoDraw* piano = new PianoDraw(this);
        PianoControls* piano_controls = new PianoControls(this);

        sizer->Add(piano_controls, 0, wxEXPAND | wxALL, 5);
        sizer->Add(piano, 1, wxEXPAND | wxALL, 5);
        this->SetSizer(sizer);
    }
};

class MyFrame : public wxFrame{
public:
    MyFrame() : wxFrame(nullptr, wxID_ANY, "Validador de notas y acordes", wxDefaultPosition, wxSize(600, 250)){
        wxBoxSizer* mainSizer = new wxBoxSizer(wxHORIZONTAL);

        LeftPanel* left = new LeftPanel(this);
        PianoPanel* piano = new PianoPanel(this);

        mainSizer->Add(left, 1, wxEXPAND | wxALL, 5);
        mainSizer->Add(piano, 2, wxEXPAND | wxALL, 5);

        this->SetSizer(mainSizer);
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



