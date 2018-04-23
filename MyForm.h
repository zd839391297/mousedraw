#pragma once
#include<stdlib.h>
namespace MouseMoveTracking {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void) :in_process(false), if_anti(false)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^  pctMain;
	protected:
	private: System::Windows::Forms::TextBox^  txtMouseX;
	private: System::Windows::Forms::TextBox^  txtMouseY;
	private: System::Windows::Forms::TextBox^  Area;



	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->pctMain = (gcnew System::Windows::Forms::PictureBox());
			this->txtMouseX = (gcnew System::Windows::Forms::TextBox());
			this->txtMouseY = (gcnew System::Windows::Forms::TextBox());
			this->Area = (gcnew System::Windows::Forms::TextBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pctMain))->BeginInit();
			this->SuspendLayout();
			// 
			// pctMain
			// 
			this->pctMain->BackColor = System::Drawing::Color::White;
			this->pctMain->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pctMain->Location = System::Drawing::Point(12, 39);
			this->pctMain->Name = L"pctMain";
			this->pctMain->Size = System::Drawing::Size(725, 394);
			this->pctMain->TabIndex = 0;
			this->pctMain->TabStop = false;
			this->pctMain->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::pctMain_Paint);
			this->pctMain->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pctMain_MouseDown);
			this->pctMain->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pctMain_MouseMove);
			this->pctMain->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pctMain_MouseUp);

			// 
			// txtMouseX
			// 
			this->txtMouseX->Location = System::Drawing::Point(12, 12);
			this->txtMouseX->Name = L"txtMouseX";
			this->txtMouseX->Size = System::Drawing::Size(100, 21);
			this->txtMouseX->TabIndex = 1;
			// 
			// txtMouseY
			// 
			this->txtMouseY->Location = System::Drawing::Point(118, 12);
			this->txtMouseY->Name = L"txtMouseY";
			this->txtMouseY->Size = System::Drawing::Size(100, 21);
			this->txtMouseY->TabIndex = 2;
			// 
			// Area
			// 
			this->Area->Location = System::Drawing::Point(224, 12);
			this->Area->Name = L"Area";
			this->Area->Size = System::Drawing::Size(100, 21);
			this->Area->TabIndex = 3;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(749, 445);
			this->Controls->Add(this->Area);
			this->Controls->Add(this->txtMouseY);
			this->Controls->Add(this->txtMouseX);
			this->Controls->Add(this->pctMain);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->Resize += gcnew System::EventHandler(this, &MyForm::MyForm_Resize);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pctMain))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		System::Collections::Generic::List<System::Drawing::Rectangle> ^StaticRects;
		System::Collections::Generic::List<System::Drawing::Rectangle> ^DynamicRects;
		System::Collections::Generic::List<System::Drawing::Rectangle> ^AntiDynamicRects;
		bool if_anti;
		bool in_process;
	private: System::Void AdjustTextArea()// A function that aims to adjust the text area while you are drag the border.
	{
		int m = 5;
		pctMain->Top = 12 + txtMouseX->Height + m;
		pctMain->Left = 0;
		pctMain->Width = this->ClientSize.Width;
		pctMain->Height = this->ClientSize.Height - txtMouseX->Height - m * 2;
	}
	private: System::Void pctMain_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
	{
		int t_x = e->Location.X;
		int t_y = e->Location.Y;
		txtMouseX->Text = t_x.ToString();
		txtMouseY->Text = t_y.ToString();
		if (!in_process) return;
		Rectangle tr;
		tr = DynamicRects[0];
		tr.Width = abs(t_x - tr.X);
		tr.Height = abs(t_y - tr.Y);
		/*if (t_x > tr.X)
		{
		if_anti = false;
		tr.Width = t_x - tr.X;
		}
		else
		{
		if_anti = true;
		tr.Width = tr.X - t_x;
		}
		if (t_y > tr.Y)
		{
		if_anti = false;
		tr.Height = t_y - tr.Y;
		}
		else
		{
		if_anti = true;
		tr.Height = tr.Y - t_y;
		}*/
		if (t_x < tr.X || t_y < tr.Y)
			if_anti = true;
		else
			if_anti = false;
		Area->Text = (tr.Width*tr.Height).ToString();
		if (if_anti) {
			Rectangle atr;
			if (t_x < tr.X)
				atr.X = t_x;
			else
				atr.X = tr.X;
			if (t_y < tr.Y)
				atr.Y = t_y;
			else
				atr.Y = tr.Y;
			atr.Width = tr.Width;
			atr.Height = tr.Height;
			AntiDynamicRects->Clear();
			AntiDynamicRects->Add(atr);
			/*if (t_x < tr.X)
			AntiDynamicRects[0].X = t_x;
			else
			AntiDynamicRects[0].X = tr.X;
			if (t_y < tr.Y)
			AntiDynamicRects[0].Y = t_y;
			else
			AntiDynamicRects[0].Y = tr.Y;
			AntiDynamicRects[0].Width = tr.Width;
			AntiDynamicRects[0].Height = tr.Height;*/
		}
		DynamicRects->Clear();
		DynamicRects->Add(tr);
		pctMain->Invalidate();
	}
	private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e)
	{
		AdjustTextArea();
		StaticRects = gcnew System::Collections::Generic::List<
			System::Drawing::Rectangle>();
		DynamicRects = gcnew System::Collections::Generic::List<
			System::Drawing::Rectangle>();
		AntiDynamicRects = gcnew System::Collections::Generic::List<
			System::Drawing::Rectangle>();
	}
	private: System::Void pctMain_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
	{
		in_process = true;
		Rectangle tr;
		tr.X = e->Location.X;
		tr.Y = e->Location.Y;
		tr.Width = 0;
		tr.Height = 0;
		DynamicRects->Add(tr);
		AntiDynamicRects->Add(tr);
	}

	private: System::Void pctMain_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
	{
		in_process = false;
		Rectangle tr;
		/*tr.X = DynamicRects[0].X;
		tr.Y = DynamicRects[0].Y;
		tr.Width = e->Location.X - tr.X;
		tr.Height = e->Location.Y - tr.Y; */
		if (e->Location.X >DynamicRects[0].X)
		{
			tr.X = DynamicRects[0].X;
			tr.Width = e->Location.X - tr.X;
		}
		else
		{
			tr.X = e->Location.X;
			tr.Width = DynamicRects[0].X - tr.X;
		}
		if (e->Location.Y >DynamicRects[0].Y)
		{
			tr.Y = DynamicRects[0].Y;
			tr.Height = e->Location.Y - tr.Y;
		}
		else
		{
			tr.Y = e->Location.Y;
			tr.Height = DynamicRects[0].Y - tr.Y;
		}
		StaticRects->Add(tr);
		DynamicRects->Clear();
		AntiDynamicRects->Clear();
		pctMain->Invalidate();
	}
	private: System::Void pctMain_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e)
	{
		for each (Rectangle r in StaticRects)
		{
			e->Graphics->DrawRectangle(gcnew Pen(System::Drawing::Color::Black, 3), r);
		}
		if (in_process)
		{
			if (if_anti)
				e->Graphics->DrawRectangle(gcnew Pen(System::Drawing::Color::Black, 3), AntiDynamicRects[0]);
			else
				e->Graphics->DrawRectangle(gcnew Pen(System::Drawing::Color::Black, 3), DynamicRects[0]);
		}
	}

	private: System::Void MyForm_Resize(System::Object^  sender, System::EventArgs^  e) {
		AdjustTextArea();
	}
	};
}