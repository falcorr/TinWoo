#include <filesystem>
#include "ui/MainApplication.hpp"
#include "ui/instPage.hpp"
#include "util/config.hpp"

#define COLOR(hex) pu::ui::Color::FromHex(hex)

namespace inst::ui {
    extern MainApplication *mainApp;

    instPage::instPage() : Layout::Layout() {    	
    		this->infoRect = Rectangle::New(0, 95, 1280, 60, COLOR("#00000080"));
    		this->SetBackgroundColor(COLOR("#000000FF"));
    		this->topRect = Rectangle::New(0, 0, 1280, 94, COLOR("#000000FF"));
        
    		if (inst::config::gayMode) {
    			if (std::filesystem::exists(inst::config::appDir + "/images/Install.png")) this->titleImage = Image::New(0, 0, (inst::config::appDir + "/images/Install.png"));
    			else this->titleImage = Image::New(0, 0, "romfs:/images/logo.png");
    			if (std::filesystem::exists(inst::config::appDir + "/images/Background.png")) this->SetBackgroundImage(inst::config::appDir + "/images/Background.png");
    			else this->SetBackgroundImage("romfs:/images/Background.png");
                this->appVersionText = TextBlock::New(0, 0, "", 0);
            }
        else {
    			this->SetBackgroundImage("romfs:/images/Background.png");
                this->titleImage = Image::New(0, 0, "romfs:/images/logo.png");
                this->appVersionText = TextBlock::New(0, 0, "", 0);
            }
        this->appVersionText->SetColor(COLOR("#FFFFFFFF"));
        this->pageInfoText = TextBlock::New(10, 109, "", 30);
        this->pageInfoText->SetColor(COLOR("#FFFFFFFF"));
        //this->installInfoText = TextBlock::New(15, 568, "", 22);
        this->installInfoText = TextBlock::New(15, 648, "", 22);
        this->installInfoText->SetColor(COLOR("#FFFFFFFF"));
        //this->installBar = pu::ui::elm::ProgressBar::New(10, 600, 850, 40, 100.0f);
        this->installBar = pu::ui::elm::ProgressBar::New(10, 680, 1260, 30, 100.0f);
        this->installBar->SetColor(COLOR("#000000FF"));
        this->installBar->SetProgressColor(COLOR("#565759FF"));
        this->Add(this->topRect);
        this->Add(this->infoRect);
        this->Add(this->titleImage);
        this->Add(this->appVersionText);
        this->Add(this->pageInfoText);
        this->Add(this->installInfoText);
        this->Add(this->installBar);
    }

    void instPage::setTopInstInfoText(std::string ourText){
        mainApp->instpage->pageInfoText->SetText(ourText);
        mainApp->CallForRender();
    }

    void instPage::setInstInfoText(std::string ourText){
        mainApp->instpage->installInfoText->SetText(ourText);
        mainApp->CallForRender();
    }

    void instPage::setInstBarPerc(double ourPercent){
        mainApp->instpage->installBar->SetVisible(true);
        mainApp->instpage->installBar->SetProgress(ourPercent);
        mainApp->CallForRender();
    }

    void instPage::loadMainMenu(){
        mainApp->LoadLayout(mainApp->mainPage);
    }

    void instPage::loadInstallScreen(){
        mainApp->instpage->pageInfoText->SetText("");
        mainApp->instpage->installInfoText->SetText("");
        mainApp->instpage->installBar->SetProgress(0);
        mainApp->instpage->installBar->SetVisible(false);
        mainApp->LoadLayout(mainApp->instpage);
        mainApp->CallForRender();
    }

    void instPage::onInput(u64 Down, u64 Up, u64 Held, pu::ui::Touch Pos) {
    }
}
