
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
};

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
	pDoc->mBackground->setscreensize(CPoint(1024,768));
	pDoc->mBackground->setspeed(12);
	pDoc->mBackground->init(0);
	

	plane_self.mAnimation = pDoc->manimation_enemy;
	plane_self.setproperty(pDoc->mplane_property[0]);
	plane_self.setDoc(pDoc);
	plane_self.level = 0;
	plane_self.exp = 0;

	mgamesetting.mission_killed = 4;


	//HRESULT hr = DirectSoundCreate8(NULL, &lpDirectSound, NULL));

	
	if (!DSlist1.Init())
		AfxMessageBox(L"声卡初始化失败");
	CString wave_path=GetModuleDir()+L"\\sound\\";
	DSlist1.AddNewBuffer(wave_path + "back.wav");  //buffer 0
	DSlist1.AddNewBuffer(wave_path + "back.wav");  //buffer 0
	DSlist1.PlayBuffer(0, 1);
	this->SetTimer(1,100,NULL);//draw
	this->SetTimer(4, 100, NULL);//generateenemy
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
void CMFCApplication3View::FireSetting() {
	CMFCApplication3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (key_space) {//我方飞机发射导弹
		int bulletid = 0;

		//发射普通导弹
		if (plane_self.cooldown_fire[bulletid] < plane_self.mproperty->mbullet_set->cooldown[bulletid]) {
			plane_self.cooldown_fire[bulletid] += 100;
		}
		else {
			plane_self.cooldown_fire[bulletid] = 0;
			plane_self.fire(&pDoc->list_bullet_general_self, 0);

		}


		//发射追踪弹
		if (!pDoc->list_airplane_enemy.IsEmpty()) {
			bulletid = 1;

			if (plane_self.cooldown_fire[bulletid] < plane_self.mproperty->mbullet_set->cooldown[bulletid]) {
				plane_self.cooldown_fire[bulletid] += 100;
			}
			else {
				plane_self.cooldown_fire[bulletid] = 0;
				plane_self.fire_trace(&pDoc->list_bullet_general_self, (FlyingObject *)pDoc->list_airplane_enemy.GetHead());

			}


		}

	
	}
	if (mgamesetting.bossmode) {//boss发射导弹

		static int boss_bulletid = 0;
		if (plane_boss->cooldown_fire[boss_bulletid] < plane_boss->mproperty->mbullet_set->cooldown[boss_bulletid]) {
			plane_boss->cooldown_fire[boss_bulletid] += 100;
			
		}
		else {
			plane_boss->cooldown_fire[boss_bulletid] = 0;
			plane_boss->fire(&pDoc->list_bullet_general_enemy, 0);

		}
		//boss_bulletid++;
		if (boss_bulletid >= plane_boss->mproperty->mbullet_set->num_set) {
			boss_bulletid = 0;
		}
	
	}

	if (!pDoc->list_airplane_enemy.IsEmpty()) {
		
	
		for (POSITION pos = pDoc->list_airplane_enemy.GetHeadPosition(); pos != NULL;)
		{
			POSITION del_airplane_enemy = pos;
			int bulletid = 0;
			PlaneEmenyGeneral *temp = (PlaneEmenyGeneral *)pDoc->list_airplane_enemy.GetNext(pos);
			if (temp->cooldown_fire [bulletid]< temp->mproperty->mbullet_set->cooldown[bulletid]) {
				temp->cooldown_fire[bulletid] += 100;
				continue;
			}
			temp->fire(&pDoc->list_bullet_general_enemy, bulletid);
			temp->cooldown_fire[bulletid] = 0;
		}

	}



};
void CMFCApplication3View::JudgeFlyingObject() {
	static float t = 0;
	CMFCApplication3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	plane_self.calculate_location();

	for (POSITION pos = pDoc->list_bullet_general_self.GetHeadPosition(); pos != NULL;)//我发子弹碰撞销毁
	{
		POSITION del = pos;
		BulletGeneral *temp = (BulletGeneral *)pDoc->list_bullet_general_self.GetNext(pos);
		temp->calculate_location();
		if (temp->finished) {
			delete temp;
			pDoc->list_bullet_general_self.RemoveAt(del);
			continue;
		}
	}


	for (POSITION pos = pDoc->list_bullet_general_enemy.GetHeadPosition(); pos != NULL;)//我方战机与敌方子弹碰撞检测
	{
		POSITION del = pos;
		BulletGeneral *temp = (BulletGeneral *)pDoc->list_bullet_general_enemy.GetNext(pos);
		temp->calculate_location();
		CRect temp_rect = CRect(temp->getlocation());
		temp_rect.bottom *= temp->property->scale;
		temp_rect.right *= temp->property->scale;

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
			delete temp;
			pDoc->list_bullet_general_enemy.RemoveAt(del);
			continue;
		}
		
		//temp->Draw(&MemDC);
	}


	for (POSITION pos = pDoc->list_airplane_enemy.GetHeadPosition(); pos != NULL;)
	{
		POSITION del_airplane_enemy = pos;
		PlaneEmenyGeneral *temp = (PlaneEmenyGeneral *)pDoc->list_airplane_enemy.GetNext(pos);
		temp->calculate_location();
		if (plane_self.isCollsion(temp->getlocation())) {//我方战机与敌方战机碰撞
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

		for (POSITION pos1 = pDoc->list_bullet_general_self.GetHeadPosition(); pos1 != NULL;) {//我方子弹与敌方战机
			POSITION del_bullet = pos1;
			BulletGeneral *temp1 = (BulletGeneral *)pDoc->list_bullet_general_self.GetNext(pos1);
			temp1->calculate_location();
			CRect temp_rect = CRect(temp1->getlocation());
			temp_rect.bottom *= temp1->property->scale;
			temp_rect.right *= temp1->property->scale;


			if (temp->isCollsion(temp_rect)) {
				temp->attack(temp1);
				temp1->finished = 1;
				Explosion *temp_explo;
				temp_explo = new Explosion();
				temp_explo->setAnimation(pDoc->manimation_explosion);
				temp_explo->setpos(CPoint(temp1->pos));
				temp_explo->windowsize = pDoc->windowssize;
				temp_explo->type = 0;
				delete temp1;
				pDoc->list_bullet_general_self.RemoveAt(del_bullet);
				pDoc->list_explosion.AddTail((CObject*)temp_explo);
				//pDoc->list_bullet_general_self.RemoveAll();
			}
			
		}
		if (temp->hp <= 0) {//敌方战机销毁
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
		}
		if (temp->finished) {
			delete temp;

			pDoc->list_airplane_enemy.RemoveAt(del_airplane_enemy);
			continue;
		}		
		t += 0.1;
		continue;
	}




	for (POSITION pos = pDoc->list_explosion.GetHeadPosition(); pos != NULL;)//爆炸销毁
	{
		POSITION del = pos;
		Explosion *temp = (Explosion *)pDoc->list_explosion.GetNext(pos);
		//temp->calculate_location();
		if (temp->finished) {
			pDoc->list_explosion.RemoveAt(del);
			continue;
		}
		
	}

	if (mgamesetting.bossmode == 1) {//boss 模式检测
		plane_boss->calculate_location();
		if (plane_boss->finished == 1)return;
		//boss与我方飞机碰撞检测
		if (plane_boss->isCollsion(plane_self.getlocation())) {
			plane_boss->attack(&plane_self);
			Explosion *temp_explo;
			temp_explo = new Explosion();
			temp_explo->setAnimation(pDoc->manimation_explosion);
			temp_explo->setpos(CPoint(plane_self.pos));
			temp_explo->windowsize = pDoc->windowssize;
			temp_explo->type = 0;
			pDoc->list_explosion.AddTail((CObject*)temp_explo);
			if (plane_boss->hp <= 0) {
				plane_boss->finished = 1;
				
			}
		}

		//boss与我方子弹碰撞检测
		for (POSITION pos1 = pDoc->list_bullet_general_self.GetHeadPosition(); pos1 != NULL;) {
			POSITION del_bullet = pos1;
			BulletGeneral *temp1 = (BulletGeneral *)pDoc->list_bullet_general_self.GetNext(pos1);
			//temp1= (BulletGeneral *)
			CRect temp_rect = CRect(temp1->getlocation());
			temp_rect.bottom *= temp1->property->scale;
			temp_rect.right *= temp1->property->scale;

			if (plane_boss->hp <= 0) {
				plane_boss->finished = 1;
				break;
			}
			if (plane_boss->isCollsion(temp_rect)) {
				plane_boss->attack(temp1);
				temp1->finished = 1;
				Explosion *temp_explo;
				temp_explo = new Explosion();
				temp_explo->setAnimation(pDoc->manimation_explosion);
				temp_explo->setpos(CPoint(temp1->pos));
				temp_explo->windowsize = pDoc->windowssize;
				temp_explo->type = 0;

				delete temp1;
				pDoc->list_bullet_general_self.RemoveAt(del_bullet);
				pDoc->list_explosion.AddTail((CObject*)temp_explo);
			}
		}



		
	
	}



};
void CMFCApplication3View::JudgeSetting() {//剧情检测
	CMFCApplication3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//飞机等级检测
	if (plane_self.exp > plane_self.mproperty->exp&&plane_self.level != 3) {//飞机升级
			plane_self.level++;
			int temp = plane_self.exp;
			plane_self.setproperty(pDoc->mplane_property[plane_self.level]);
			plane_self.exp = temp;
	}
	//关卡检测(BOSS)
	if (mgamesetting.bossmode) {
		if (plane_boss->finished) {
			if (mgamesetting.mission_present < 3) {
				mgamesetting.mission_present++;
				pDoc->mBackground->init(mgamesetting.mission_present);
			}
			pDoc->mBackground->setspeed(12);
			delete plane_boss;
			plane_boss = NULL;
			mgamesetting.bossmode = 0;

		}
		return;
	}

	//检测是否进入boss模式
	if (mgamesetting.mission_killed >= mgamesetting.mission_level[mgamesetting.mission_present]) {
			mgamesetting.bossmode = 1;
			plane_boss = new PlaneBoss();
			plane_boss->setAnimation(pDoc->manimation_enemy);
			plane_boss->setproperty(pDoc->mplane_property[mgamesetting.bossid[mgamesetting.mission_present]]);
			plane_boss->setDoc(pDoc);
			plane_boss->setequation(pDoc->mmove_equation_set[9]);
			plane_boss->setvelociety(50);
			plane_boss->setoffset(CPoint(150, 150));
			pDoc->mBackground->setspeed(0);
			return;
	}

	//普通模式产生飞机
	if (pDoc->list_airplane_enemy.GetCount() < 4) {
		if (mgamesetting.cooldown_plane_generate[0] < mgamesetting.cooldown_plane_generate[1]) { mgamesetting.cooldown_plane_generate[0] += 100; return; }
		mgamesetting.cooldown_plane_generate[0] = 0;
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

		temp->setequation(pDoc->mmove_equation_set[option2]);
		temp->setvelociety(50);
		pDoc->list_airplane_enemy.AddTail((CObject*)temp);
	}

};
afx_msg void CMFCApplication3View::OnTimer(UINT_PTR nIDEvent) {
	using namespace Gdiplus;
	long t1 = GetTickCount();
	CClientDC DC(this);
	CRect rect;
	CBitmap MemBitmap;//?????
	
	
	CMFCApplication3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	switch (nIDEvent) {
	case 1:{
		int c = 1;
		this->GetClientRect(rect);
		MemBitmap.CreateCompatibleBitmap(&DC, rect.Width(), rect.Height());
		MemDC.SelectObject(&MemBitmap);
		MemDC.FillSolidRect(rect, RGB(255, 255, 255));
		pDoc->mBackground->drawbackground(&MemDC);
		plane_self.draw(&MemDC);
		for (POSITION pos = pDoc->list_bullet_general_self.GetHeadPosition(); pos != NULL;)//绘制我方子弹
		{
			POSITION del = pos;
			BulletGeneral *temp = (BulletGeneral *)pDoc->list_bullet_general_self.GetNext(pos);
			temp->Draw(&MemDC);
		}
		for (POSITION pos = pDoc->list_bullet_general_enemy.GetHeadPosition(); pos != NULL;)//绘制敌方子弹
		{
			POSITION del = pos;
			BulletGeneral *temp = (BulletGeneral *)pDoc->list_bullet_general_enemy.GetNext(pos);
			temp->Draw(&MemDC);
		}
		for (POSITION pos = pDoc->list_airplane_enemy.GetHeadPosition(); pos != NULL;)//绘制敌方战机
		{
			POSITION del_airplane_enemy = pos;
			PlaneEmenyGeneral *temp = (PlaneEmenyGeneral *)pDoc->list_airplane_enemy.GetNext(pos);
			temp->draw(&MemDC);
			continue;
		}
		for (POSITION pos = pDoc->list_explosion.GetHeadPosition(); pos != NULL;)//绘制爆炸
		{
			POSITION del = pos;
			Explosion *temp = (Explosion *)pDoc->list_explosion.GetNext(pos);
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
		//AfxTrace(str);//获取系统运行时间 　　
		break;
	}

	case 4:
		JudgeSetting();
		JudgeFlyingObject();
		FireSetting();
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
			//auto aa = temp_json_equation.dump();
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
		temp_plane->mbullet_set->cooldown = new int[temp_plane->mbullet_set->num_set+1];
		
		temp_plane->mbullet_set->bullet = new struct bullet_property**[json_bullet_set_bullet.size()+1];
		//configure bullet property
		

		for (int j = 0; j < json_bullet_set_all.size(); j++) {//traverse single set
			json json_bullet_set_each = json_bullet_set_bullet[j];
			temp_plane->mbullet_set->bullet[j] = new struct bullet_property*[json_bullet_set_each["bullet_property"].size()+1];
			if (!json_bullet_set_each["cooldown"].is_null()) {
				temp_plane->mbullet_set->cooldown[j] = json_bullet_set_each["cooldown"];
			}
			else {
				temp_plane->mbullet_set->cooldown[j] = 2000;
			}
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
		key_space = 1;
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
		key_space = 0;
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
