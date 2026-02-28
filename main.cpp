#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <wx/wx.h>
#include <wx/dcbuffer.h>
#include <wx/tglbtn.h>

using namespace std;

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

        unordered_map<string, vector<string>> scaleMap = {
            {"CM",  {"C","D","E","F","G","A","B"}},
            {"GM",  {"G","A","B","C","D","E","F#"}},
            {"DM",  {"D","E","F#","G","A","B","C#"}},
            {"AM",  {"A","B","C#","D","E","F#","G#"}},
            {"EM",  {"E","F#","G#","A","B","C#","D#"}},
            {"BM",  {"B","C#","D#","E","F#","G#","A#"}},
            {"F#M", {"F#","G#","A#","B","C#","D#","E#"}},
            {"C#M", {"C#","D#","E#","F#","G#","A#","B#"}},

            {"FM",  {"F","G","A","Bb","C","D","E"}},
            {"BbM", {"Bb","C","D","Eb","F","G","A"}},
            {"EbM", {"Eb","F","G","Ab","Bb","C","D"}},
            {"AbM", {"Ab","Bb","C","Db","Eb","F","G"}},

            {"Am",  {"A","B","C","D","E","F","G"}},
            {"Em",  {"E","F#","G","A","B","C","D"}},
            {"Bm",  {"B","C#","D","E","F#","G","A"}},
            {"F#m", {"F#","G#","A","B","C#","D","E"}},
            {"C#m", {"C#","D#","E","F#","G#","A","B"}},
            {"G#m", {"G#","A#","B","C#","D#","E","F#"}},
            {"D#m", {"D#","E#","F#","G#","A#","B","C#"}},
            {"A#m", {"A#","B#","C#","D#","E#","F#","G#"}},

            {"Dm",  {"D","E","F","G","A","Bb","C"}},
            {"Gm",  {"G","A","Bb","C","D","Eb","F"}},
            {"Cm",  {"C","D","Eb","F","G","Ab","Bb"}},
            {"Fm",  {"F","G","Ab","Bb","C","Db","Eb"}}
        };

        unordered_map<string, vector<string>> chordMap = {
            {"CM",   {"C","E","G"}},
            {"Cm",  {"C","Eb","G"}},
            {"C7",  {"C","E","G","Bb"}},
            {"Cm7", {"C","Eb","G","Bb"}},

            {"C#M",   {"C#","E#","G#"}},
            {"C#m",  {"C#","E","G#"}},
            {"C#7",  {"C#","E#","G#","B"}},
            {"C#m7", {"C#","E","G#","B"}},

            {"DbM",   {"Db","F","Ab"}},
            {"Dbm",  {"Db","Fb","Ab"}},
            {"Db7",  {"Db","F","Ab","Cb"}},
            {"Dbm7", {"Db","Fb","Ab","Cb"}},

            {"DM",   {"D","F#","A"}},
            {"Dm",  {"D","F","A"}},
            {"D7",  {"D","F#","A","C"}},
            {"Dm7", {"D","F","A","C"}},

            {"D#M",   {"D#","F##","A#"}},
            {"D#m",  {"D#","F#","A#"}},
            {"D#7",  {"D#","F##","A#","C#"}},
            {"D#m7", {"D#","F#","A#","C#"}},

            {"EbM",   {"Eb","G","Bb"}},
            {"Ebm",  {"Eb","Gb","Bb"}},
            {"Eb7",  {"Eb","G","Bb","Db"}},
            {"Ebm7", {"Eb","Gb","Bb","Db"}},

            {"EM",   {"E","G#","B"}},
            {"Em",  {"E","G","B"}},
            {"E7",  {"E","G#","B","D"}},
            {"Em7", {"E","G","B","D"}},

            {"FM",   {"F","A","C"}},
            {"Fm",  {"F","Ab","C"}},
            {"F7",  {"F","A","C","Eb"}},
            {"Fm7", {"F","Ab","C","Eb"}},

            {"F#M",   {"F#","A#","C#"}},
            {"F#m",  {"F#","A","C#"}},
            {"F#7",  {"F#","A#","C#","E"}},
            {"F#m7", {"F#","A","C#","E"}},

            {"GbM",   {"Gb","Bb","Db"}},
            {"Gbm",  {"Gb","Bbb","Db"}},
            {"Gb7",  {"Gb","Bb","Db","Fb"}},
            {"Gbm7", {"Gb","Bbb","Db","Fb"}},

            {"GM",   {"G","B","D"}},
            {"Gm",  {"G","Bb","D"}},
            {"G7",  {"G","B","D","F"}},
            {"Gm7", {"G","Bb","D","F"}},

            {"G#M",   {"G#","B#","D#"}},
            {"G#m",  {"G#","B","D#"}},
            {"G#7",  {"G#","B#","D#","F#"}},
            {"G#m7", {"G#","B","D#","F#"}},

            {"AbM",   {"Ab","C","Eb"}},
            {"Abm",  {"Ab","Cb","Eb"}},
            {"Ab7",  {"Ab","C","Eb","Gb"}},
            {"Abm7", {"Ab","Cb","Eb","Gb"}},

            {"AM",   {"A","C#","E"}},
            {"Am",  {"A","C","E"}},
            {"A7",  {"A","C#","E","G"}},
            {"Am7", {"A","C","E","G"}},

            {"A#M",   {"A#","C##","E#"}},
            {"A#m",  {"A#","C#","E#"}},
            {"A#7",  {"A#","C##","E#","G#"}},
            {"A#m7", {"A#","C#","E#","G#"}},

            {"BbM",   {"Bb","D","F"}},
            {"Bbm",  {"Bb","Db","F"}},
            {"Bb7",  {"Bb","D","F","Ab"}},
            {"Bbm7", {"Bb","Db","F","Ab"}},

            {"BM",   {"B","D#","F#"}},
            {"Bm",  {"B","D","F#"}},
            {"B7",  {"B","D#","F#","A"}},
            {"Bm7", {"B","D","F#","A"}}
        };

        string tonalidad = "CM";
        string secuencia = "C E G";

        string note = "";
        vector<string> incorrectNotes;
        bool isValid = true;
        for(char& c : secuencia){
            if(c == ' '){
                if(std::find(scaleMap[tonalidad].begin(), scaleMap[tonalidad].end(), note) == scaleMap[tonalidad].end()){
                    if(chordMap.find(note) != chordMap.end()){
                        for(string& chordNote : chordMap[note]){
                            if(std::find(scaleMap[tonalidad].begin(), scaleMap[tonalidad].end(), chordNote) == scaleMap[tonalidad].end()){
                                incorrectNotes.push_back(note);
                                isValid = false;
                            }
                        }
                    }
                    incorrectNotes.push_back(note);
                    isValid = false;
                }
                note = "";
            }
            else{
                note += c;
            }
                
            
        }


        MyFrame* frame = new MyFrame();
        frame->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(MyApp);



