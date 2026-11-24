#include "ayush.h"
/* SAMPLE dataset. Replace codes with the official NAMASTE / ICD-11 TM2 sheet before real use. */
Entry db[] = {
{"Amavata","Ayurveda","NAMC-AY-001","TM2-A-001","amavata,joint pain,swelling,stiffness","Simhanada Guggulu; Rasna decoction","Before food, warm water","Warm light foods, ginger, old rice, moong soup","Curd, cold drinks, heavy fried food, day sleep",0},
{"Jwara","Ayurveda","NAMC-AY-002","TM2-A-002","jwara,fever,chills,body ache,temperature","Sudarshana Churna","After light food, warm water","Rice gruel, moong soup, warm water","Heavy meals, exertion, cold exposure",0},
{"Kasa","Ayurveda","NAMC-AY-003","TM2-A-003","kasa,cough,dry cough,phlegm,throat","Sitopaladi Churna with honey","Morning and evening","Warm water, light food, turmeric milk","Cold and sour foods, ice cream, curd at night",0},
{"Prameha","Ayurveda","NAMC-AY-004","TM2-A-004","prameha,frequent urination,thirst,fatigue","Chandraprabha Vati; Nisha-Amalaki","Before meals","Barley, bitter gourd, millets, daily walking","Sugar, sweets, sedentary routine, day sleep",0},
{"Amlapitta","Ayurveda","NAMC-AY-005","TM2-A-005","amlapitta,acidity,heartburn,burning,sour belching,nausea","Avipattikar Churna","Before meals","Cooling light foods, coconut water, ripe banana","Spicy, fried, fermented food, late dinners",0},
{"Shiroroga","Ayurveda","NAMC-AY-006","TM2-A-006","shiroroga,headache,migraine,head pain","Pathyadi Kwatha; Anu Taila Nasya","Morning, per physician","Regular meals, adequate sleep, warm water","Fasting, sun exposure, loud noise, late nights",0},
{"Suda","Unani","NAMU-UN-001","TM2-U-001","suda,headache,migraine,head pain","Roghan-e-Gul (rose oil) application","As advised by hakim","Cooling, light diet; adequate fluids","Spicy food, sleeplessness, excess heat",0},
{"Thamaga Swasam","Siddha","NAMS-SI-001","TM2-S-001","thamaga swasam,breathlessness,wheezing,asthma,shortness of breath","Aadathodai manapagu","Morning, per physician","Warm, light, freshly cooked food","Cold drinks, dust, curd, heavy night meals",0}
};
int ND = sizeof db / sizeof db[0];
