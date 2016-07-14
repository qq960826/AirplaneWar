
// MFCApplication3View.cpp : CMFCApplication3View 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MFCApplication3.h"
#endif

#include "MFCApplication3Doc.h"
#include "MFCApplication3View.h"
//#include "json/json.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplication3View

IMPLEMENT_DYNCREATE(CMFCApplication3View, CView)

BEGIN_MESSAGE_MAP(CMFCApplication3View, CView)
	// 标准打印命令

	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
END_MESSAGE_MAP()

// CMFCApplication3View 构造/析构

CMFCApplication3View::CMFCApplication3View()
{
	
	// TODO: 在此处添加构造代码

}

CMFCApplication3View::~CMFCApplication3View()
{
	//(_T("WZQ"), _T("wzq"), 4);
}

BOOL CMFCApplication3View::PreCreateWindow(CREATESTRUCT& cs)
{

	return CView::PreCreateWindow(cs);
}

// CMFCApplication3View 绘制

void CMFCApplication3View::OnDraw(CDC* /*pDC*/)
{
	CMFCApplication3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CMFCApplication3View 打印

BOOL CMFCApplication3View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMFCApplication3View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMFCApplication3View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CMFCApplication3View 诊断

#ifdef _DEBUG
void CMFCApplication3View::AssertValid() const
{
	CView::AssertValid();
}

void CMFCApplication3View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCApplication3Doc* CMFCApplication3View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApplication3Doc)));
	return (CMFCApplication3Doc*)m_pDocument;
}
#endif //_DEBUG
CString GetModuleDir()
{
	HMODULE module = GetModuleHandle(0);
	TCHAR pFileName[MAX_PATH];
	GetModuleFileName(module, pFileName, MAX_PATH);

	CString csFullPath(pFileName);
	int nPos = csFullPath.ReverseFind(_T('\\'));
	if (nPos < 0)
		return CString("");
	else
		return csFullPath.Left(nPos);
}
void CMFCApplication3View::OnInitialUpdate() {
	CView::OnInitialUpdate();
	
	CMFCApplication3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CRect rect;
	this->GetClientRect(rect);

	pDoc->windowssize = new CPoint(rect.right-rect.left, 666);

	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	MemDC.CreateCompatibleDC(NULL);
	LoadImageFromFile();
	InitalizeAirplane();
	InitializeEquation();
	pDoc->mBackground = new Background();
	pDoc->mBackground->mAnimation = pDoc->manimation_background;
	pDoc->mBackground->setscreensize(CPoint(512,768));
	pDoc->mBackground->setspeed(12);
	pDoc->mBackground->init(1);


	plane_self.mAnimation = pDoc->manimation_enemy;
	plane_self.setproperty(pDoc->mplane_property[0]);
	plane_self.setDoc(pDoc);
	plane_self.level = 0;
	plane_self.exp = 0;
	this->SetTimer(1,100,NULL);//draw
	this->SetTimer(2, 2000, NULL);//generateenemy
	this->SetTimer(3, 3000, NULL);//generateenemy
}
CString GetWorkDir()
{
	TCHAR currentDir[MAX_PATH];
	int nPos=GetCurrentDirectory(MAX_PATH, currentDir);

	CString csFullPath(currentDir);
	if (nPos < 0)
		return CString("");
	else
		return csFullPath;
}

afx_msg void CMFCApplication3View::OnTimer(UINT_PTR nIDEvent) {
	using namespace Gdiplus;
	long t1 = GetTickCount();
	CClientDC DC(this);
	CRect rect;
	CBitmap MemBitmap;//?????
	
	static float t = 0;
	CMFCApplication3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	switch (nIDEvent) {
	case 1:{
		//MoveWindow(0, 0, 100, 100, TRUE);



		this->GetClientRect(rect);
		MemBitmap.CreateCompatibleBitmap(&DC, rect.Width(), rect.Height());
		MemDC.SelectObject(&MemBitmap);
		MemDC.FillSolidRect(rect, RGB(255, 255, 255));



		pDoc->mBackground->drawbackground(&MemDC, 3);
		plane_self.draw(&MemDC);
		// pos;
		for (POSITION pos = pDoc->list_bullet_general_self.GetHeadPosition(); pos != NULL;)
		{
			POSITION del = pos;
			BulletGeneral *temp = (BulletGeneral *)pDoc->list_bullet_general_self.GetNext(pos);
			if (temp->finished) {
				pDoc->list_bullet_general_self.RemoveAt(del);
				continue;
			}
			temp->Draw(&MemDC);
		}



		for (POSITION pos = pDoc->list_bullet_general_enemy.GetHeadPosition(); pos != NULL;)
		{
			POSITION del = pos;
			BulletGeneral *temp = (BulletGeneral *)pDoc->list_bullet_general_enemy.GetNext(pos);
			CRect temp_rect = CRect(temp->getlocation());
			temp_rect.bottom *= temp->property->scale;
			temp_rect.right *= temp->property->scale;
			//temp_rect.top += temp_rect.bottom;
			//temp_rect.left += temp_rect.right / 2;
			if (plane_self.isCollsion(temp_rect)) {
				plane_self.attack(temp);
				temp->finished = 1;

				Explosion *temp_explo;
				temp_explo = new Explosion();
				temp_explo->setAnimation(pDoc->manimation_explosion);
				temp_explo->type = 0;
				temp_explo->setpos(CPoint(temp->pos.x + (temp->objectsize.x*temp->property->scale) / 2, temp->pos.y + (temp->objectsize.y*temp->property->scale)));
				temp_explo->windowsize = pDoc->windowssize;
				pDoc->list_explosion.AddTail((CObject*)temp_explo);
			}
			if (temp->finished) {
				pDoc->list_bullet_general_enemy.RemoveAt(del);
				continue;
			}
			temp->Draw(&MemDC);
		}
		for (POSITION pos = pDoc->list_airplane_enemy.GetHeadPosition(); pos != NULL;)
		{
			POSITION del_airplane_enemy = pos;
			PlaneEmenyGeneral *temp = (PlaneEmenyGeneral *)pDoc->list_airplane_enemy.GetNext(pos);

			if (plane_self.isCollsion(temp->getlocation())) {
				if (temp->cooldown_collision < 3) {//collison colddown
					temp->cooldown_collision++;

				}
				else {
					temp->cooldown_collision = 0;
					Explosion *temp_explo;
					plane_self.attack(temp);
					temp_explo = new Explosion();
					temp_explo->setAnimation(pDoc->manimation_explosion);
					temp_explo->setpos(CPoint(plane_self.pos));
					temp_explo->windowsize = pDoc->windowssize;
					temp_explo->type = 0;
					pDoc->list_explosion.AddTail((CObject*)temp_explo);
				}
			}

			for (POSITION pos1 = pDoc->list_bullet_general_self.GetHeadPosition(); pos1 != NULL;) {
				POSITION del_bullet = pos1;
				BulletGeneral *temp1 = (BulletGeneral *)pDoc->list_bullet_general_self.GetNext(pos1);
				//temp1= (BulletGeneral *)
				CRect temp_rect = CRect(temp1->getlocation());
				temp_rect.bottom *= temp1->property->scale;
				temp_rect.right *= temp1->property->scale;


				if (temp->isCollsion(temp_rect)) {
					//temp->isCollsion(temp1->getlocation());
					temp->attack(temp1);
					temp1->finished = 1;
					Explosion *temp_explo;
					temp_explo = new Explosion();
					temp_explo->setAnimation(pDoc->manimation_explosion);
					temp_explo->setpos(CPoint(temp1->pos));
					temp_explo->windowsize = pDoc->windowssize;
					temp_explo->type = 0;
					pDoc->list_bullet_general_self.RemoveAt(del_bullet);
					pDoc->list_explosion.AddTail((CObject*)temp_explo);
					//pDoc->list_bullet_general_self.RemoveAll();
				}

			}
			if (temp->hp <= 0) {
				Explosion *temp_explo;
				temp_explo = new Explosion();
				temp_explo->setAnimation(pDoc->manimation_explosion);
				temp_explo->setpos(CPoint(temp->pos));
				temp_explo->windowsize = pDoc->windowssize;
				temp_explo->type = 1;
				pDoc->list_explosion.AddTail((CObject*)temp_explo);

				temp->finished = 1;
				mgamesetting.mission_killed++;
				plane_self.exp += temp->exp;


				CString s; s.Format(_T("%d\n"), plane_self.exp);
				AfxTrace(s);
			}
			if (temp->finished) {
				//delete[] temp1 ;

				pDoc->list_airplane_enemy.RemoveAt(del_airplane_enemy);
				continue;
			}

			//pDoc->list_bullet_general_self.RemoveAt(pos)
			t += 0.1;
			
			//temp->setvelocity(CPoint(sin(t)*20,cos(t)*20));
			temp->draw(&MemDC);
			continue;
		}
		for (POSITION pos = pDoc->list_explosion.GetHeadPosition(); pos != NULL;)
		{
			POSITION del = pos;
			Explosion *temp = (Explosion *)pDoc->list_explosion.GetNext(pos);

			temp->Draw(&MemDC);
			if (temp->finished) {
				pDoc->list_explosion.RemoveAt(del);
				continue;
			}
			temp->Draw(&MemDC);
		}
		if (plane_boss != NULL) {
			plane_boss->draw(&MemDC);
		}


		Gdiplus::Graphics graphics(MemDC);
		// Initialize arguments.
		Gdiplus::Font myFont(L"Arial", 10);
		RectF layoutRect(0.0f, 0.0f, 200.0f, 50.0f);
		StringFormat format;
		//format.SetAlignment(StringAlignmentCenter);
		SolidBrush blackBrush(Color(255, 255, 0, 0));

		// Draw string.
		CString str1; str1.Format(L"HP:%d\nEXP:%d", plane_self.hp, plane_self.exp);
		graphics.DrawString(
			str1,
			20,
			&myFont,
			layoutRect,
			&format,
			&blackBrush);

		// Draw layoutRect.

		DC.BitBlt(0, 0, rect.Width(), rect.Height(), &MemDC, 0, 0, SRCCOPY);
		long t2 = GetTickCount();//程序段结束后取得系统运行时间(ms) 　　
		CString str;
		str.Format(L"time:%dms\n", t2 - t1);//前后之差即 程序运行时间 　　
		AfxTrace(str);//获取系统运行时间 　　
		break;
	}
	case 2: {//关卡设置
		if (plane_self.exp > plane_self.mproperty->exp&&plane_self.level!=3) {//飞机升级
			plane_self.level++;
			plane_self.setproperty(pDoc->mplane_property[plane_self.level]);

			//plane_self.setDoc(pDoc);
		}
		//if()
		if (pDoc->list_airplane_enemy.GetCount() > 4)return;
		if (mgamesetting.bossmode==1&& plane_boss!=NULL) {//
			if (plane_boss->hp <= 0) {
				delete plane_boss;
				plane_boss = NULL;
				mgamesetting.bossmode = 0;
				if (mgamesetting.mission_present < 3) {
					mgamesetting.mission_present++;
				}
			}
			else 
			{
				return;
			}
			

		}
		if (mgamesetting.mission_killed >= mgamesetting.mission_level[mgamesetting.mission_present]) {
			mgamesetting.bossmode = 1;
			plane_boss= new PlaneBoss();
			plane_boss->setAnimation(pDoc->manimation_enemy);
			plane_boss->setproperty(pDoc->mplane_property[16]);
			plane_boss->setDoc(pDoc);
			plane_boss->setvelocity(CPoint(0, 0));
			plane_boss->setacceleration(CPoint(0, 0));
			plane_boss->setpos(CPoint(150, 150));
			return;



		}
		int selection[] = { 4,5,6,7,8,9,10,11,12,13,15 };
		srand((unsigned)time(NULL));
		PlaneEmenyGeneral *temp;
		temp = new PlaneEmenyGeneral();
		int option1, option2;
		option1 = rand() % 11;
		option2 = rand() % pDoc->mplane_property[selection[option1]]->equation_num;

		temp->setAnimation(pDoc->manimation_enemy);
		temp->setproperty(pDoc->mplane_property[selection[option1]]);
		temp->setDoc(pDoc);
		//temp->setvelocity(CPoint(0, 0));
		//temp->setacceleration(CPoint(0, 0));
		//temp->setoffset(CPoint(150, 150));
		temp->setequation(pDoc->mmove_equation_set[option2]);
		temp->setvelociety(50);
		//temp->setHP(10);
		//temp->setAttack(1);

		pDoc->list_airplane_enemy.AddTail((CObject*)temp);


		//pDoc->list_airplane_enemy.AddTail((CObject*)temp);


		break; }
	case 3://ennemy launch the bullet
		if (pDoc->list_airplane_enemy.IsEmpty()) {
			return;


		}
	PlaneEmenyGeneral *temp_airplane_enemy = (PlaneEmenyGeneral *)pDoc->list_airplane_enemy.GetHead();
		if (!temp_airplane_enemy) return;
		temp_airplane_enemy->fire(&pDoc->list_bullet_general_enemy,0);

		break;
	};


	
};
void CMFCApplication3View::InitializeEquation() {
	CMFCApplication3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	using json = nlohmann::json;

	CStdioFile f1(GetModuleDir() + L"\\config_equation.json", CFile::typeText);
	CString all = L"";
	CString test;
	while (f1.ReadString(test)) {
		all += test;
	}
	f1.Close();
	CT2CA pszConvertedAnsiString(all);
	std::string strStd(pszConvertedAnsiString);
	json json_fromfile = json::parse(strStd);
	

	pDoc->mmove_equation_set = new move_equation_set *[json_fromfile.size()];
	for (int i = 0; i < json_fromfile.size(); i++) {
		struct move_equation_set* temp_plane = new move_equation_set;
		temp_plane->id = json_fromfile[i]["id"];
		temp_plane->loop = json_fromfile[i]["loop"];
		int temp_equation_num = json_fromfile[i]["equation"].size();
		temp_plane->offset.x = json_fromfile[i]["offset"]["x"];
		temp_plane->offset.y = json_fromfile[i]["offset"]["y"];
		temp_plane->num_equation = temp_equation_num;
		temp_plane->move_equation = new move_equation*[temp_equation_num+1];


		for (int j = 0; j < temp_equation_num; j++) {
			auto temp_json_equation = json_fromfile[i]["equation"][j];
			auto aa = temp_json_equation.dump();
			temp_plane->move_equation[j] = new move_equation;
			temp_plane->move_equation[j]->x.base = temp_json_equation["x"]["base"];
			temp_plane->move_equation[j]->x.increment = temp_json_equation["x"]["increment"];
			temp_plane->move_equation[j]->x.target = temp_json_equation["x"]["target"];
			{std::string a = temp_json_equation["x"]["expression"];
			temp_plane->move_equation[j]->x.equation = a; }

			temp_plane->move_equation[j]->y.base = temp_json_equation["y"]["base"];
			temp_plane->move_equation[j]->y.increment = temp_json_equation["y"]["increment"];
			temp_plane->move_equation[j]->y.target = temp_json_equation["y"]["target"];
			{std::string a = temp_json_equation["y"]["expression"];
			temp_plane->move_equation[j]->y.equation = a; }





		}
		pDoc->mmove_equation_set[i] = temp_plane;
		



	}


}
void CMFCApplication3View::InitalizeAirplane() {
	CMFCApplication3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	using json = nlohmann::json;

	CStdioFile f1(GetModuleDir() +L"\\config.json", CFile::typeText);
	CString all =L"";
	CString test;
	while (f1.ReadString(test)) {
		all += test;
	}
	f1.Close();
	CT2CA pszConvertedAnsiString(all);
	std::string strStd(pszConvertedAnsiString);
	json json_fromfile= json::parse(strStd);
	

	pDoc->mplane_property = new plane_property * [json_fromfile.size()];
	for (int i = 0; i < json_fromfile.size(); i++) {//traverse all the plane
		struct plane_property* temp_plane = new plane_property ;

		temp_plane->id= json_fromfile[i]["id"];
		temp_plane->hp = json_fromfile[i]["hp"];
		temp_plane->attack = json_fromfile[i]["attack"];
		temp_plane->pictureid = json_fromfile[i]["pictureid"];
		temp_plane->exp = json_fromfile[i]["exp"];

		if (!json_fromfile[i]["equationid"].is_null()) {
			temp_plane->equation_num = json_fromfile[i]["equationid"].size();
			temp_plane->equation_id = new int[temp_plane->equation_num+1];
			for (int l = 0; l < temp_plane->equation_num; l++) {
				temp_plane->equation_id[l] = json_fromfile[i]["equationid"][l];

			
			}

		}


		//configure bulletset
		json json_bullet_set_all = json_fromfile[i]["bullet_set"];
		temp_plane->mbullet_set = new struct bullet_set;
		temp_plane->mbullet_set->id = json_bullet_set_all["id"];
		auto json_bullet_set_bullet = json_bullet_set_all["bullet"];
		temp_plane->mbullet_set->num_set = json_bullet_set_bullet.size();
		temp_plane->mbullet_set->bullet = new struct bullet_property**[json_bullet_set_bullet.size()+1];
		//configure bullet property
		

		for (int j = 0; j < json_bullet_set_all.size(); j++) {//traverse single set
			json json_bullet_set_each = json_bullet_set_bullet[j];
			temp_plane->mbullet_set->bullet[j] = new struct bullet_property*[json_bullet_set_each["bullet_property"].size()+1];
			
			if (!j)temp_plane->mbullet_set->num_each = new int [json_bullet_set_each["bullet_property"].size()+1];

			temp_plane->mbullet_set->num_each[j] = json_bullet_set_each["bullet_property"].size();
			for (int k = 0; k < json_bullet_set_each["bullet_property"].size(); k++) {//traverse the element in the single set
				json json_bullet_each = json_bullet_set_each["bullet_property"][k];
				temp_plane->mbullet_set->bullet[j][k] = new struct bullet_property;
				temp_plane->mbullet_set->bullet[j][k]->id= json_bullet_each["id"];
				temp_plane->mbullet_set->bullet[j][k]->attack = json_bullet_each["attack"];
				temp_plane->mbullet_set->bullet[j][k]->pictureid = json_bullet_each["pictureid"];
				temp_plane->mbullet_set->bullet[j][k]->rotation = json_bullet_each["rotation"];
				temp_plane->mbullet_set->bullet[j][k]->scale = json_bullet_each["scale"];
				temp_plane->mbullet_set->bullet[j][k]->speed = json_bullet_each["speed"];
				temp_plane->mbullet_set->bullet[j][k]->offset = new CPoint(json_bullet_each["offset"][0], json_bullet_each["offset"][1]);
				
			}
		
		}
		pDoc->mplane_property[i] = temp_plane;
	
	}

}

// CMFCApplication3View 消息处理程序
void CMFCApplication3View::LoadImageFromFile() {
	CMFCApplication3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//Load own airplane resource
	Image *temp;
	pDoc->manimation_airplane_self = new Animation(1);
	temp= Image::FromFile(GetModuleDir() + "\\img_plane_main.png");
	int temp1[]= { 1,91,124,78,
		268,106,116,70,
		0,0,134,89,
		268,0,122,103,

		393,102,115,92,
		392,0,118,99,
		127,107,115,93,
		137,0,129,104,

		0,266,109,83,
		0,351,94,83,
		115,202,109,88,
		0,172,113,92,

		226,258,106,79,
		111,292,102,76,
		359,196,108,81,
		244,179,113,77
	};
	pDoc->manimation_airplane_self->addimage(temp, temp1, 16);

	//load background
	pDoc->manimation_background = new Animation(5);
	CString a;
	for (int i = 1; i <= 5; i++) {
		a.Format(_T("%d"), i);
		temp=Image::FromFile(GetModuleDir() + "\\background_"+ a +".jpg");
		pDoc->manimation_background->addimage(temp);
	
	}


	//load enemy airplane
	pDoc->manimation_enemy = new Animation(29);
	for (int i = 1; i <= 29; i++) {
		a.Format(_T("%d"), i);
		temp = Image::FromFile(GetModuleDir() + "\\img_plane_enemy\\img_plane_enemy" + a + ".png");
		pDoc->manimation_enemy->addimage(temp);

	}




	//load explosion
	pDoc->manimation_explosion = new Animation(1);
	temp = Image::FromFile(GetModuleDir() + "\\explosion.png");
	int temp4[] = { 
		76,497,8,8,//bullet explosion
		76,473,22,22,
		2,473,36,36,
		599,458,50,50,
		599,392,64,64,
		665,392,56,58,
		651,458,44,44,
		40,473,36,36,


	};

	pDoc->manimation_explosion->addimage(temp, temp4, 8);
	int temp5[] = {
		415,405,92,92,//general airplane explode
		706,262,128,128,
		719,2,128,128,
		706,132,128,128,
		576,262,128,128,
		589,2,128,128,
		576,132,128,128,
		723,392,40,40

	};
	pDoc->manimation_explosion->addimage(temp, temp5, 8);



	pDoc->manimation_bullet = new Animation(30);
	for (int i = 0; i < 30; i++) {
		a.Format(_T("%d"), i);
		temp = Image::FromFile(GetModuleDir() + "\\img_bullet\\img_bullet"+a+".png");
		pDoc->manimation_bullet->addimage(temp);
	}


	pDoc->manimation_hp = new Animation(2);
	temp = Image::FromFile(GetModuleDir() + "\\img_other\\img_hp1.png");
	pDoc->manimation_hp->addimage(temp);
	temp = Image::FromFile(GetModuleDir() + "\\img_other\\img_hp2.png");
	pDoc->manimation_hp->addimage(temp);
}

void CMFCApplication3View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

}


void CMFCApplication3View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CMFCApplication3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch (nChar) {
	case VK_SPACE:
		plane_self.fire(&pDoc->list_bullet_general_self,0);
		break;
	case VK_LEFT:
		plane_self.velocity.x = -10;
		break;
	case VK_RIGHT:
		plane_self.velocity.x = 10;
		break;
	case VK_UP:
		plane_self.velocity.y = -10;
		break;
	case VK_DOWN:
		plane_self.velocity.y = 10;
		break;
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CMFCApplication3View::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch (nChar) {
	case VK_SPACE:
		//plane_self.velocity.y = 0;
		break;
	case VK_LEFT:
		plane_self.velocity.x = 0;
		break;
	case VK_RIGHT:
		plane_self.velocity.x = 0;
		break;
	case VK_UP:
		plane_self.velocity.y = 0;
		break;
	case VK_DOWN:
		plane_self.velocity.y = 0;
		break;
	}
	CView::OnKeyUp(nChar, nRepCnt, nFlags);
}
