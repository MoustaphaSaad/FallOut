#include"basicShader.h"
#include"Camera.h"
#include"Application.h"
#include"DepthTexture.h"
#include"Core.h"
#include"Scene.h"
#include"Light.h"
#include"VisualObject.h"
#include"VisualComposer.h"
using namespace Fallout;

void BasicShader::Update(Transformable* obj, Material* mtl){
		Scene* scene = Engine::getInstance()->getApplication()->getScene();
		View = Engine::getInstance()->getApplication()->getScene()->getCamera()->getPositionRotation();
		Projection = Engine::getInstance()->getApplication()->getScene()->getCamera()->getProjection();
		Model = obj->getTransform()->getModel();
		this->setUniform("View",View.Transpose());
		this->setUniform("Projection", Projection.Transpose());
		this->setUniform("Model",Model.Transpose());

		this->setUniform("fogStart",fogStart);
		this->setUniform("fogEnd",fogEnd);
		this->setUniform("fogEnabled",fogEnabled);
		this->setUniform("fogColor",fogColor);
		this->setUniform("ApplyNormal",mtl->hasNormalMap());
		
		this->setUniform("receiveShadow",obj->Composer->receiveShadow);
		this->setUniform("LIGHTNUM",scene->getLightsCount());
		for(int i=0;i<scene->getLightsCount();i++){
			string text = "Lights[";
			text+=i+48;
			text+="]";
			this->setUniform(text+".pos",scene->getLight(i)->getPosition());
			this->setUniform(text+".la",scene->getLight(i)->getLa());
			this->setUniform(text+".ld",scene->getLight(i)->getLd());
			this->setUniform(text+".ls",scene->getLight(i)->getLs());
			this->setUniform(text+".intensity",scene->getLight(i)->getIntensity());
		}
		this->setUniform("LIGHTDIRNUM",scene->getDirLightsCount());
		for(int i=0;i<scene->getDirLightsCount();i++){
			string name;
			if(i==0){
				name = "dirLight0";
				BindTexture(scene->getDirLight(i)->getShadow()->ShadowBuffer->getDepth(),"shadowMap0");
				//scene->getDirLight(i)->getShadow()->BlurTexture.reset();
			}
			else if (i ==1){
				name = "dirLight1";
				BindTexture(scene->getDirLight(i)->getShadow()->ShadowBuffer->getDepth(),"shadowMap1");
				//scene->getDirLight(i)->getShadow()->BlurTexture.reset();
			}
			else if (i==2){
				name = "dirLight2";
				BindTexture(scene->getDirLight(i)->getShadow()->ShadowBuffer->getDepth(),"shadowMap2");
				//scene->getDirLight(i)->getShadow()->BlurTexture.reset();
			}
			this->setUniform(name + ".pos", scene->getDirLight(i)->getPosition());
			this->setUniform(name + ".la", scene->getDirLight(i)->getLa());
			this->setUniform(name + ".ld", scene->getDirLight(i)->getLd());
			this->setUniform(name + ".ls", scene->getDirLight(i)->getLs());
			this->setUniform(name + ".dir", scene->getDirLight(i)->getDirection());
			this->setUniform(name + ".intensity", scene->getDirLight(i)->getIntensity());
			this->setUniform(name + ".shadowMatrix", scene->getDirLight(i)->getShadowMatrix().Transpose());
			

		}

		this->setUniform("Epos", scene->getCamera()->getTransform()->position);

	}


const string BasicShader::content = 
	"#version 330\n"

	"attribute vec3 position;\n"
	"attribute vec3 normal;\n"
	"attribute vec3 color;\n"
	"attribute vec2 texCoord;\n"
	"attribute vec3 tangent;\n"

	"struct lightInfo{\n"
		"vec3 pos;\n"
		"vec3 la;\n"
		"vec3 ld;\n"
		"vec3 ls;\n"
		"float intensity;\n"
	"};\n"
	"struct DirLight{\n"
		"vec3 pos;\n"
		"vec3 dir;\n"
		"vec3 la;\n"
		"vec3 ld;\n"
		"vec3 ls;\n"
		"float intensity;\n"
		"mat4 shadowMatrix;\n"
	"};\n"
	"struct materialInfo{\n"
		"vec3 ka;\n"
		"vec3 kd;\n"
		"vec3 ks;\n"
		"float shine;\n"
	"};\n"
	"struct lightOut{\n"
	"	vec3 la;\n"
	"	vec3 ld;\n"
	"	vec3 ls;\n"
	"};\n"
	
	"fragment lightOut calcLight(lightInfo light,vec3 pos,vec3 norm,materialInfo Mat){\n"
	"	lightOut res;\n"
	"	vec3 lpos = light.pos;\n"
		"float dist = length(pos-lpos);\n"
		"float att = 1.0/(1.0+0.01*dist+0.001*dist*dist);\n"
		"vec3 ambient = Mat.ka*light.la;\n"

		"vec3 surf2light=normalize(lpos-pos);\n"
		"vec3 N = normalize(norm);\n"
		"float dcont = max(0.0,dot(N,surf2light));\n"
		"vec3 diffuse=dcont*(Mat.kd*light.ld);\n"

		"vec3 surf2view=normalize(-pos);\n"
		"vec3 reflection = reflect(-surf2light,N);\n"

		"float scont = pow(max(0.0,dot(surf2view,-reflection)),Mat.shine);\n"
		"vec3 specular = scont*light.ls*Mat.ks;\n"

		"res.la = ambient*att*light.intensity;\n"
		"res.ld = diffuse*att*light.intensity;\n"
		"res.ls = specular*att*light.intensity;\n"

		"return res;\n"
	"}\n"

	"fragment lightOut CalcDirLight(DirLight light,vec3 pos,vec3 normal,vec3 epos,materialInfo Mat){\n"
		"lightOut res;\n"

		"float df = dot(normal,-light.dir);\n"

		"vec4 dc = vec4(0,0,0,0);\n"
		"vec4 ds = vec4(0,0,0,0);\n"

		"if(df>0){\n"
			"dc = vec4(light.ld,1.0)*df*vec4(Mat.kd,1.0);\n"
			"vec3 dirToE = normalize(epos - pos);\n"
			"vec3 hd = normalize(dirToE - light.dir);\n"

			"float sf = dot(hd,normal);\n"

			"if(sf >0)\n"
			"{\n"
				"ds = vec4(light.ls,1.0)*sf*vec4(Mat.ks,1.0);\n"
			"}\n"
		"}\n"
		"res.la = (light.la*Mat.ka)*light.intensity;\n"
		"res.ld = vec3(dc)*light.intensity;\n"
		"res.ls = vec3(ds)*light.intensity;\n"
		"return res;\n"
	"}\n"

	"bool InRange(float val,float minVal, float maxVal){\n"
		"if(val>=minVal && val<=maxVal)\n"
			"return true;\n"
		"return false;\n"
	"}\n"
	"float sampleRSM(sampler2D Dmap,vec2 coor,float compare){\n"
		"return step(compare, texture2D(Dmap, coor).r);\n"
	"}\n"
	"float calcShadow(sampler2D Dmap, vec4 coor){\n"
	
		"vec4 sh = vec4((coor.xyz/coor.w),1);\n"
		"sh.z-=0.05;\n"
		"if(InRange(sh.z,0,1) && InRange(sh.x,0,1) && InRange(sh.y,0,1)){\n"
			"return sampleRSM(Dmap,sh.xy,sh.z);\n"
		"}else{\n"
			"return 1.0;\n"
		"}\n"
	"}\n"

	"vec4 shadowDebug(sampler2D Dmap,vec4 coor){\n"
		"//vec4 sh = vec4((coor.xyz/coor.w),1);\n"
		"//float val = SampleVSM(Dmap,sh);\n"
		"return vec4(0);\n"
		"//return texture2D(Dmap,coor.xy);\n"
	"}\n"
	"varying vec3 Position;\n"
	"varying vec3 Normal;\n"
	"varying vec2 ftexCoord;\n"
	"varying vec3 Color;\n"
	"varying mat4 mf;\n"
	"varying mat3 tbnMatrix;\n"


	"vuniform mat4 View;\n"
	"vuniform mat4 Projection;\n"
	"vuniform mat4 Model;\n"



	"funiform sampler2D Tex;\n"
	"funiform bool ApplyNormal;\n"
	"funiform bool receiveShadow;\n"
	"funiform vec3 fogColor;\n"
	"funiform sampler2D NormalTex;\n"
	"funiform vec3 Epos;\n"
	"funiform float fogStart;\n"
	"funiform float fogEnd;\n"
	"funiform bool fogEnabled;\n"


	"funiform lightInfo Lights[10];\n"
	"funiform DirLight dirLight0;\n"
	"funiform DirLight dirLight1;\n"
	"funiform DirLight dirLight2;\n"
	"funiform sampler2D shadowMap0;\n"
	"funiform sampler2D shadowMap1;\n"
	"funiform sampler2D shadowMap2;\n"
	"funiform int LIGHTNUM;\n"
	"funiform int LIGHTDIRNUM;\n"
	"funiform materialInfo Mat;\n"

	"fragment float ComputeFogFactor(float d,float fs,float fe)\n"
	"{\n"
		"if(fogEnabled)\n"
			"return clamp((d - fs) / (fe - fs), 0, 1);\n"
		"else\n"
		"	return 0;\n"
	"}\n"

	"void VSmain()\n"
	"{\n"

	
		"mf = Model;\n"
		"mat3 Nm = mat3(Model);\n"
		"Nm = inverse(Nm);\n"
		"Nm = transpose(Nm);\n"
		"Color = color;\n"
		"Position = vec3(Model*vec4(position,1));\n"
		"Normal = normalize(Nm*normal);\n"
		"ftexCoord = texCoord;\n"

		"vec3 n = normalize((Model * vec4(normal, 0.0)).xyz);\n"
		"vec3 t = normalize((Model * vec4(tangent, 0.0)).xyz);\n"
		"t = normalize(t - dot(t, n) * n);\n"
    
		"vec3 biTangent = cross(t, n);\n"
		"tbnMatrix = mat3(t, biTangent, n);\n"

		"gl_Position = Projection*View*Model*vec4(position,1.0);\n"
	"}\n"

	"void FSmain()\n"
	"{\n"
		"vec3 MEINNORMAL = Normal;\n"
		"if(ApplyNormal)\n"
			"MEINNORMAL = normalize(tbnMatrix * (255.0/128.0 * texture2D(NormalTex, ftexCoord).xyz - 1));\n"

		"float fogFactor = ComputeFogFactor(distance(Epos,Position),fogStart,fogEnd);\n"
		"//Adding the lights\n"

		"//check if there's a texture\n"
		"vec4 texC = texture(Tex,ftexCoord);\n"

		"lightOut totalDir;\n"
		"totalDir.la= vec3(0,0,0);\n"
		"totalDir.ld= vec3(0,0,0);\n"
		"totalDir.ls= vec3(0,0,0);\n"

		"lightOut outd0;\n"
		"lightOut outd1;\n"
		"lightOut outd2;\n"
		"float c0,c1,c2;\n"

		"outd0.la = vec3(0);\n"
		"outd0.ld = vec3(0);\n"
		"outd0.ls = vec3(0);\n"

		"outd1.la = vec3(0);\n"
		"outd1.ld = vec3(0);\n"
		"outd1.ls = vec3(0);\n"

		"outd2.la = vec3(0);\n"
		"outd2.ld = vec3(0);\n"
		"outd2.ls = vec3(0);\n"

		"c0=1; c1 =1; c2=1;\n"

		"if(LIGHTDIRNUM>=1){\n"
			"outd0 = CalcDirLight(dirLight0,Position,normalize(MEINNORMAL),vec3(mf*vec4(Epos,1)),Mat);\n"
			"c0 = calcShadow(shadowMap0,dirLight0.shadowMatrix*vec4(Position,1));\n"
			"if(receiveShadow){\n"
				"outd0.ld *= c0;\n"
			"}\n"
		"}\n"
		"if(LIGHTDIRNUM>=2){\n"
			"outd1 = CalcDirLight(dirLight1,Position,normalize(MEINNORMAL),vec3(mf*vec4(Epos,1)),Mat);\n"
			
			"c1 = calcShadow(shadowMap1,dirLight1.shadowMatrix*vec4(Position,1));\n"
			"if(receiveShadow)\n"
				"outd1.ld *= c1;\n"
		"}\n"
		"if(LIGHTDIRNUM>=3){\n"
			"outd2 = CalcDirLight(dirLight2,Position,normalize(MEINNORMAL),vec3(mf*vec4(Epos,1)),Mat);\n"
			"c2 = calcShadow(shadowMap2,dirLight2.shadowMatrix*vec4(Position,1));\n"
			"if(receiveShadow)\n"
				"outd2.ld *= c2;\n"
		"}\n"

		"totalDir.la += outd0.la;\n"
		"totalDir.ld += outd0.ld;\n"
		"totalDir.ls += outd0.ls;\n"

		"totalDir.la += outd1.la;\n"
		"totalDir.ld += outd1.ld;\n"
		"totalDir.ls += outd1.ls;\n"

		"totalDir.la += outd2.la;\n"
		"totalDir.ld += outd2.ld;\n"
		"totalDir.ls += outd2.ls;\n"
	
	
		"//Calc the lights\n"
		"lightOut AP;\n"
		"AP.la=vec3(0,0,0);\n"
		"AP.ld=vec3(0,0,0);\n"
		"AP.ls=vec3(0,0,0);\n"
		
		
		"bool fp=true;\n"
		"for(int i=0;i<LIGHTNUM;i++){\n"
			"lightOut ith = calcLight(Lights[i],Position,normalize(MEINNORMAL),Mat);\n"
		
			
			"if(LIGHTNUM<=1){\n"
				"AP.la = ith.la;\n"
				"AP.ld = ith.ld;\n"
				"AP.ls = ith.ls;\n"
			"}else if(fp){\n"
				"i++;\n"
				"lightOut ith2 = calcLight(Lights[i],Position,normalize(MEINNORMAL),Mat);\n"
				"AP.la = ith.la+ith2.la;\n"
				"AP.ld = ith.ld+ith2.ld;\n"
				"AP.ls = ith.ls+ith2.ls;\n"
				"fp = false;\n"
			"}else{\n"
				"AP.la += ith.la;\n"
				"AP.ld += ith.ld;\n"
				"AP.ls += ith.ls;\n"
			"}\n"
		
		"}\n"

		"lightOut totalLight;\n"
		"totalLight.la = (AP.la+totalDir.la)*Mat.ka;\n"
		"totalLight.ld = ((AP.ld+totalDir.ld)+(Color+ vec3(texC) ))*Mat.kd;\n"
		"totalLight.ls = (AP.ls+totalDir.ls)*Mat.ks;\n"

		/*
		if(c0<1)
			totalLight.ld *= (dirLight0.intensity)/max(((dirLight0.intensity*dirLight0.intensity)-dirLight0.intensity),1);
		if(c1<1)
			totalLight.ld *= (dirLight1.intensity)/max(((dirLight1.intensity*dirLight1.intensity)-dirLight1.intensity),1);
		if(c2<1)
			totalLight.ld *= (dirLight2.intensity)/max(((dirLight2.intensity*dirLight2.intensity)-dirLight2.intensity),1);
		*/
		
		
		"vec4 finale = vec4((totalLight.la+totalLight.ld+totalLight.ls) , 1.0);\n"
		"gl_FragColor = vec4(mix((totalLight.la+totalLight.ld+totalLight.ls),fogColor,fogFactor),1);\n"
		//gl_FragColor = shadowDebug(shadowMap0,dirLight0.shadowMatrix*vec4(Position,1));

	"}\n";