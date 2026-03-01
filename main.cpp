#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <wx/wx.h>
#include <wx/dcbuffer.h>
#include <wx/tglbtn.h>

using namespace std;

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
            {"CM",  {"C","E","G"}},
            {"Cm",  {"C","Eb","G"}},
            {"C7",  {"C","E","G","Bb"}},
            {"Cm7", {"C","Eb","G","Bb"}},

            {"C#M",  {"C#","E#","G#"}},
            {"C#m",  {"C#","E","G#"}},
            {"C#7",  {"C#","E#","G#","B"}},
            {"C#m7", {"C#","E","G#","B"}},

            {"DbM",  {"Db","F","Ab"}},
            {"Dbm",  {"Db","Fb","Ab"}},
            {"Db7",  {"Db","F","Ab","Cb"}},
            {"Dbm7", {"Db","Fb","Ab","Cb"}},

            {"DM",   {"D","F#","A"}},
            {"Dm",   {"D","F","A"}},
            {"D7",   {"D","F#","A","C"}},
            {"Dm7",  {"D","F","A","C"}},

            {"D#M",  {"D#","F##","A#"}},
            {"D#m",  {"D#","F#","A#"}},
            {"D#7",  {"D#","F##","A#","C#"}},
            {"D#m7", {"D#","F#","A#","C#"}},

            {"EbM",  {"Eb","G","Bb"}},
            {"Ebm",  {"Eb","Gb","Bb"}},
            {"Eb7",  {"Eb","G","Bb","Db"}},
            {"Ebm7", {"Eb","Gb","Bb","Db"}},

            {"EM",   {"E","G#","B"}},
            {"Em",   {"E","G","B"}},
            {"E7",   {"E","G#","B","D"}},
            {"Em7",  {"E","G","B","D"}},

            {"FM",   {"F","A","C"}},
            {"Fm",   {"F","Ab","C"}},
            {"F7",   {"F","A","C","Eb"}},
            {"Fm7",  {"F","Ab","C","Eb"}},

            {"F#M",   {"F#","A#","C#"}},
            {"F#m",   {"F#","A","C#"}},
            {"F#7",   {"F#","A#","C#","E"}},
            {"F#m7",  {"F#","A","C#","E"}},

            {"GbM",   {"Gb","Bb","Db"}},
            {"Gbm",   {"Gb","Bbb","Db"}},
            {"Gb7",   {"Gb","Bb","Db","Fb"}},
            {"Gbm7",  {"Gb","Bbb","Db","Fb"}},

            {"GM",    {"G","B","D"}},
            {"Gm",    {"G","Bb","D"}},
            {"G7",    {"G","B","D","F"}},
            {"Gm7",   {"G","Bb","D","F"}},

            {"G#M",   {"G#","B#","D#"}},
            {"G#m",   {"G#","B","D#"}},
            {"G#7",   {"G#","B#","D#","F#"}},
            {"G#m7",  {"G#","B","D#","F#"}},

            {"AbM",   {"Ab","C","Eb"}},
            {"Abm",   {"Ab","Cb","Eb"}},
            {"Ab7",   {"Ab","C","Eb","Gb"}},
            {"Abm7",  {"Ab","Cb","Eb","Gb"}},

            {"AM",    {"A","C#","E"}},
            {"Am",    {"A","C","E"}},
            {"A7",    {"A","C#","E","G"}},
            {"Am7",   {"A","C","E","G"}},

            {"A#M",   {"A#","C##","E#"}},
            {"A#m",   {"A#","C#","E#"}},
            {"A#7",   {"A#","C##","E#","G#"}},
            {"A#m7",  {"A#","C#","E#","G#"}},

            {"BbM",   {"Bb","D","F"}},
            {"Bbm",   {"Bb","Db","F"}},
            {"Bb7",   {"Bb","D","F","Ab"}},
            {"Bbm7",  {"Bb","Db","F","Ab"}},

            {"BM",    {"B","D#","F#"}},
            {"Bm",    {"B","D","F#"}},
            {"B7",    {"B","D#","F#","A"}},
            {"Bm7",   {"B","D","F#","A"}}
        };

    unordered_map<string, int> noteToIndex = {
            {"C", 0}, {"C#", 1}, {"Db", 1},
            {"D", 2}, {"D#", 3}, {"Eb", 3},
            {"E", 4}, {"E#", 5}, {"Fb", 4},
            {"F", 5}, {"F#", 6}, {"Gb", 6},
            {"G", 7}, {"G#", 8}, {"Ab", 8},
            {"A", 9}, {"A#",10}, {"Bb",10},
            {"B",11}, {"B#",0},{"Cb",11}
        };

vector<string> validateSequence(const string& tonalidad, const string& secuencia){
    string note = "";
    vector<string> incorrectNotes;

    for(const char& c : secuencia){
        if(c == ' '){ // separar notas por espacios
            if(!note.empty()){
                if(std::find(scaleMap[tonalidad].begin(), scaleMap[tonalidad].end(), note) == scaleMap[tonalidad].end()){
                    if(chordMap.find(note) != chordMap.end()){
                        for(const string& chordNote : chordMap[note]){
                            if(std::find(scaleMap[tonalidad].begin(), scaleMap[tonalidad].end(), chordNote) == scaleMap[tonalidad].end()){
                                incorrectNotes.push_back(note);
                                break; // evitar duplicados
                            }
                        }
                    }
                    else{
                        incorrectNotes.push_back(note);
                    }
                }
                note = "";
            }
        }
        else{
            note += c;
        }
    }

    //Validar la última nota si no terminó en espacio
    if(!note.empty()){
        if(std::find(scaleMap[tonalidad].begin(), scaleMap[tonalidad].end(), note) == scaleMap[tonalidad].end()){
            if(chordMap.find(note) != chordMap.end()){
                for(const string& chordNote : chordMap[note]){
                    if(std::find(scaleMap[tonalidad].begin(), scaleMap[tonalidad].end(), chordNote) == scaleMap[tonalidad].end()){
                        incorrectNotes.push_back(note);
                        break;
                    }
                }
            }
            else{
                incorrectNotes.push_back(note);
            }
        }
    }

    return incorrectNotes;
}

class LeftPanel : public wxPanel{
public:
    LeftPanel(wxWindow* parent) : wxPanel(parent){
        wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

        wxStaticText* text_tonality = new wxStaticText(this, wxID_ANY, "Tonalidad");
        tone_note = new wxChoice(this, wxID_ANY);
        for (const auto& pair : scaleMap) {
            tone_note->Append(pair.first);
        }

        wxStaticText* text_sequence = new wxStaticText(this, wxID_ANY, "Secuencia");
        field_sequence = new wxTextCtrl(this, wxID_ANY);
        wxButton* validate_sequence = new wxButton(this, wxID_ANY, "Validar");
        validate_sequence->Bind(wxEVT_BUTTON, &LeftPanel::ValidateSequence, this);

        sizer->Add(text_tonality, 0, wxALL, 5);
        sizer->Add(tone_note, 0, wxALL, 5);
        sizer->Add(text_sequence, 0, wxALL, 5);
        sizer->Add(field_sequence, 0, wxALL | wxEXPAND, 5);
        sizer->Add(validate_sequence, 0, wxALL | wxCENTER, 5);

        this->SetSizer(sizer);
    }
private:
    wxChoice* tone_note;
    wxTextCtrl* field_sequence;

    void ValidateSequence(wxCommandEvent& event){
        wxString sequence = field_sequence->GetValue();
        int sel = tone_note->GetSelection();
        if (sel == wxNOT_FOUND) {
            wxMessageBox("Selecciona una tonalidad");
            return;
        }

        wxString tonality = tone_note->GetString(sel);
        
        vector<string> incorrectNotes = validateSequence(tonality.ToStdString(), sequence.ToStdString());
        if(incorrectNotes.empty()){
            wxMessageBox("La secuencia es correcta");
        }
        else{
            wxString message = "Las siguientes notas no pertenecen a la tonalidad " + tonality + ":\n";
            for(const string& note : incorrectNotes){
                message += note + "\n";
            }
            wxMessageBox(message);
        }
    }
};

class PianoDraw : public wxPanel {
public:
    PianoDraw(wxWindow* parent) : wxPanel(parent) {
        SetBackgroundStyle(wxBG_STYLE_PAINT);
        Bind(wxEVT_PAINT, &PianoDraw::OnPaint, this);
    }
    void paintNotes(const vector<string>& notes){
        // Aquí se implementaría la lógica para pintar las notas en el piano
    }
    void paintChords(const vector<string>& chords){
        // Aquí se implementaría la lógica para pintar los acordes en el piano
    }
    void paintScale(const string& tonalidad){
        vector<string> scale = scaleMap[tonalidad]; //pintar la escala de la tonalidad seleccionada en gris claro
        paintIndexes(scale, wxColour(200, 200, 200)); // Gris claro
        
    }
    void paintIndexes(const vector<string>& scale, const wxColour& color){
        wxSize size = GetClientSize();
        wxAutoBufferedPaintDC dc(this);
        
        int keyWidth  = size.x / 8;
        int keyHeight = size.y;
        dc.SetPen(*wxBLACK_PEN);
        dc.SetBrush(wxBrush(color));

        unordered_map<int, int> transformedIndexesWhite = {
            {0, 0}, {2, 1}, {4, 2}, {5, 3}, {7, 4}, {9, 5}, {11, 6}
        };
        unordered_map<int, int> transformedIndexesBlack = {
            {1, 0}, {3, 1}, {6, 3}, {8, 4}, {10, 5}
        };

        for(const string& note : scale){
            int index =noteToIndex[note];
            if (transformedIndexesWhite.find(index) == transformedIndexesWhite.end()) continue; // Ignorar notas no válidas
            int index_mt = transformedIndexesWhite[index];
            dc.SetBrush(wxBrush(color));
            dc.DrawRectangle(index_mt * keyWidth, 0, keyWidth, keyHeight);
        }

        int blackHeight = keyHeight * 0.6;
        int blackWidth  = keyWidth / 2;

        for(const string& note : scale){
            int index = noteToIndex[note];
            if (transformedIndexesBlack.find(index) == transformedIndexesBlack.end()) continue; // Ignorar notas no válidas
            int index_mt = transformedIndexesBlack[index];
            int x = (index_mt + 1) * keyWidth - blackWidth / 2;

            dc.SetBrush(wxBrush(color));
            dc.DrawRectangle(x, 0, blackWidth, blackHeight);
        }
    }

private:
    void OnPaint(wxPaintEvent&) {
        wxAutoBufferedPaintDC dc(this);

        wxSize size = GetClientSize();
        if (size.x <= 0 || size.y <= 0) return;

        int keyWidth  = size.x / 8;
        int keyHeight = size.y;

        dc.SetPen(*wxBLACK_PEN);

        //Teclas blancas
        for (int i = 0; i < 8; ++i) {
            dc.SetBrush(*wxWHITE_BRUSH);
            dc.DrawRectangle(i * keyWidth, 0, keyWidth, keyHeight);
        }

        //Teclas negras
        int blackHeight = keyHeight * 0.6;
        int blackWidth  = keyWidth / 2;

        for (int i = 0; i < 7; ++i) {
            if (i == 2 || i == 6) continue;  

            int x = (i + 1) * keyWidth - blackWidth / 2;

            dc.SetBrush(*wxBLACK_BRUSH);
            dc.DrawRectangle(x, 0, blackWidth, blackHeight);
        }
    }
};

class PianoControls : public wxPanel{
public:
    PianoControls(wxWindow* parent) : wxPanel(parent){
        wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);

        wxToggleButton* show_notes = new wxToggleButton(this, wxID_ANY, "Notas");
        wxToggleButton* show_chords = new wxToggleButton(this, wxID_ANY, "Acordes");

        show_notes->Bind(wxEVT_TOGGLEBUTTON, &PianoControls::OnToggleNotes, this);
        show_chords->Bind(wxEVT_TOGGLEBUTTON, &PianoControls::OnToggleChords, this);

        sizer->Add(show_notes, 1, wxALL, 5);
        sizer->Add(show_chords, 1, wxALL, 5);

        this->SetSizer(sizer);
    }
private:
    void OnToggleNotes(wxCommandEvent& event){
        if(event.IsChecked()){
            
        }
    }

    void OnToggleChords(wxCommandEvent& event){
        if(event.IsChecked()){
            
        }
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
    MyFrame() : wxFrame(nullptr, wxID_ANY, "Validador de notas y acordes", wxDefaultPosition, wxSize(610, 300)){
        SetMinSize(wxSize(610, 300));
        SetMaxSize(wxSize(610, 300));
        
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