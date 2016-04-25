/*
 * glmath.hpp
 *
 *  Created on: Mar 30, 2015
 *      Author: rainautumn
 */

#include <cmath>

#ifndef GL_MATH_H_
#define GL_MATH_H_

struct vtx4
{
	float v[4];

	float *x = &v[0];
	float *y = &v[1];
	float *z = &v[2];
	float *a = &v[3];

	float l()
	{
		return sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
	}

	void orterisation()
	{
		float le = l();
		v[0] = v[0] / le;
		v[1] = v[1] / le;
		v[2] = v[2] / le;
	}

	void drop()
	{
		v[0] = 0;
		v[1] = 0;
		v[2] = 0;
		v[3] = 0;
	}

	void init(float f, float s, float t, float fo)
	{
		v[0] = f;
		v[1] = s;
		v[2] = t;
		v[3] = fo;
	}

    vtx4 operator+()
    {
        vtx4 buf_v;
        buf_v.v[0] = v[0];
        buf_v.v[1] = v[1];
        buf_v.v[2] = v[2];
        buf_v.v[3] = v[3];
        return buf_v;
        }

    vtx4 operator-()
    {
        vtx4 buf_v;
        buf_v.v[0] = -v[0];
        buf_v.v[1] = -v[1];
        buf_v.v[2] = -v[2];
        buf_v.v[3] = -v[3];
        return buf_v;
    }

    vtx4 operator+(const vtx4& w)
    {
        vtx4 buf_v;
        buf_v.v[0] = v[0] + w.v[0];
        buf_v.v[1] = v[1] + w.v[1];
        buf_v.v[2] = v[2] + w.v[2];
        buf_v.v[3] = v[3] + w.v[3];
        return buf_v;
        }

    vtx4 operator-(const vtx4& w)
    {
        vtx4 buf_v;
        buf_v.v[0] = v[0] - w.v[0];
        buf_v.v[1] = v[1] - w.v[1];
        buf_v.v[2] = v[2] - w.v[2];
        buf_v.v[3] = v[3] - w.v[3];
        return buf_v;
        }
};

struct vtx3
{
	float v[3];

	float l()
	{
		return sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
	}

    vtx3 orterisation()
	{
		float le = l();
		v[0] = v[0] / le;
		v[1] = v[1] / le;
		v[2] = v[2] / le;
        return *this;
	}

	void drop()
	{
		v[0] = 0;
		v[1] = 0;
		v[2] = 0;
	}

	void init(float f, float s, float t)
	{
		v[0] = f;
		v[1] = s;
		v[2] = t;
	}

	vtx3 operator+()
	{
		vtx3 buf_v;
		buf_v.v[0] = v[0];
		buf_v.v[1] = v[1];
		buf_v.v[2] = v[2];
		return buf_v;
	    }

	vtx3 operator-()
	{
		vtx3 buf_v;
		buf_v.v[0] = -v[0];
		buf_v.v[1] = -v[1];
		buf_v.v[2] = -v[2];
		return buf_v;
	}

	vtx3 operator+(const vtx3& w)
	{
		vtx3 buf_v;
		buf_v.v[0] = v[0] + w.v[0];
		buf_v.v[1] = v[1] + w.v[1];
		buf_v.v[2] = v[2] + w.v[2];
		return buf_v;
	    }

	vtx3 operator-(const vtx3& w)
	{
		vtx3 buf_v;
		buf_v.v[0] = v[0] - w.v[0];
		buf_v.v[1] = v[1] - w.v[1];
		buf_v.v[2] = v[2] - w.v[2];
		return buf_v;
	    }

	vtx3 &operator+=(const vtx3 &w){
		v[0] = v[0] + w.v[0];
		v[1] = v[1] + w.v[1];
		v[2] = v[2] + w.v[2];
		return *this;
	    }

	vtx3 &operator-=(const vtx3 &w){
		v[0] = v[0] - w.v[0];
		v[1] = v[1] - w.v[1];
		v[2] = v[2] - w.v[2];
		return *this;
	    }

	vtx3 operator*(const vtx3 &w)
	{
		vtx3 buf_v;
		buf_v.v[0] = v[1] * w.v[2] - v[2] * w.v[1];
		buf_v.v[1] = v[2] * w.v[0] - v[0] * w.v[2];
		buf_v.v[2] = v[0] * w.v[1] - v[1] * w.v[0];
		return buf_v;
	}

    vtx3 operator*(const float &f)
	{
		vtx3 buf_v;
		buf_v.v[0] = v[0] * f;
		buf_v.v[1] = v[1] * f;
		buf_v.v[2] = v[2] * f;
		return buf_v;
	}

    vtx3 operator/(const float &f)
	{
		vtx3 buf_v;
		buf_v.v[0] = v[0] / f;
		buf_v.v[1] = v[1] / f;
		buf_v.v[2] = v[2] / f;
		return buf_v;
	}

    void E_cos(vtx3 v)
    {
        vtx3 buf_v;
        buf_v.v[0] = cos(v.v[0]);
        buf_v.v[1] = cos(v.v[1]);
        buf_v.v[2] = cos(v.v[2]);
        *this = buf_v;
    }

    void E_sin(vtx3 v)
    {
        vtx3 buf_v;
        buf_v.v[0] = sin(v.v[0]);
        buf_v.v[1] = sin(v.v[1]);
        buf_v.v[2] = sin(v.v[2]);
        *this = buf_v;
    }

};

struct vtx2
{
float v[2];

	float l()
	{
		return sqrt(v[0]*v[0] + v[1]*v[1]);
	}

	void orterisation()
	{
		float le = l();
		v[0] = v[0] / le;
		v[1] = v[1] / le;
	}

	void drop()
	{
		v[0] = 0;
		v[1] = 0;
	}

	void init(float f, float s)
	{
		v[0] = f;
		v[1] = s;
	}

	vtx2 operator+()
	{
		vtx2 buf_v;
		buf_v.v[0] = v[0];
		buf_v.v[1] = v[1];
		return buf_v;
		}

	vtx2 operator-()
	{
		vtx2 buf_v;
		buf_v.v[0] = -v[0];
		buf_v.v[1] = -v[1];
		return buf_v;
	}

	vtx2 operator+(const vtx2& w)
	{
		vtx2 buf_v;
		buf_v.v[0] = v[0] + w.v[0];
		buf_v.v[1] = v[1] + w.v[1];
		return buf_v;
		}

	vtx2 operator-(const vtx2& w)
	{
		vtx2 buf_v;
		buf_v.v[0] = v[0] - w.v[0];
		buf_v.v[1] = v[1] - w.v[1];
		return buf_v;
		}

	vtx2 &operator+=(const vtx2 &w){
		v[0] = v[0] + w.v[0];
		v[1] = v[1] + w.v[1];
		return *this;
		}

	vtx2 &operator-=(const vtx2 &w){
		v[0] = v[0] - w.v[0];
		v[1] = v[1] - w.v[1];
		return *this;
		}

	vtx2 operator*(float &f)
	{
		vtx2 buf_v;
		buf_v.v[0] = v[0] * f;
		buf_v.v[1] = v[1] * f;
		return buf_v;
	}

	vtx2 operator/(float &f)
	{
		vtx2 buf_v;
		buf_v.v[0] = v[0] / f;
		buf_v.v[1] = v[1] / f;
		return buf_v;
	}
};

struct mtx4
{
	    float m[4][4];

	    void drop()
	    {
	    	m[0][0] = 0;	m[0][1] = 0;	m[0][2] = 0;	m[0][3] = 0;
	    	m[1][0] = 0;	m[1][1] = 0;	m[1][2] = 0;	m[1][3] = 0;
	    	m[2][0] = 0;	m[2][1] = 0;	m[2][2] = 0;	m[2][3] = 0;
	    	m[3][0] = 0;	m[3][1] = 0;	m[3][2] = 0;	m[3][3] = 0;
	    };

	    void init()
	    {
	    	m[0][0] = 1;	m[0][1] = 0;	m[0][2] = 0;	m[0][3] = 0;
	    	m[1][0] = 0;	m[1][1] = 1;	m[1][2] = 0;	m[1][3] = 0;
	    	m[2][0] = 0;	m[2][1] = 0;	m[2][2] = 1;	m[2][3] = 0;
	    	m[3][0] = 0;	m[3][1] = 0;	m[3][2] = 0;	m[3][3] = 1;
	    };

	    void scale(float s)
	    {
	    	m[0][0] = s;	m[0][1] = 0;	m[0][2] = 0;	m[0][3] = 0;
	    	m[1][0] = 0;	m[1][1] = s;	m[1][2] = 0;	m[1][3] = 0;
	    	m[2][0] = 0;	m[2][1] = 0;	m[2][2] = s;	m[2][3] = 0;
	    	m[3][0] = 0;	m[3][1] = 0;	m[3][2] = 0;	m[3][3] = 1;
	    };

        void tranform_position(
	    		struct vtx3 p)
	    {
            init();
        	m[0][3] = p.v[0];
    		m[1][3] = p.v[1];
    		m[2][3] = p.v[2];
	    };

	    void perspective(
	    		float h,
	    		float w,
				float near,
				float far)
	    {
	    	m[0][0] = 2*near / w;	m[0][1] = 0;			m[0][2] = 0;								m[0][3] = 0;
	    	m[1][0] = 0;			m[1][1] = 2*near / h;	m[1][2] = 0;								m[1][3] = 0;
	    	m[2][0] = 0;			m[2][1] = 0;			m[2][2] = (far + near) / (near - far);		m[2][3] = -2 * far * near / (far - near);
	    	m[3][0] = 0;		    m[3][1] = 0;			m[3][2] = -1;								m[3][3] = 1;
	    };


	    mtx4 operator*(mtx4 in)
	    {
	    	mtx4 buf;
	    	buf.drop();
	    	for(int i = 0; i < 4; i++)
	    		for(int j = 0; j < 4; j++)
	    			for(int k = 0; k < 4; k++)
	    				buf.m[i][j] += m[i][k] * in.m[k][j];
	    	return buf;
	    }

        void tranform_angle(
                struct vtx3 a)
	    {
            vtx3 cs;
            cs.E_cos(a);
            vtx3 sn;
            sn.E_sin(a);

        	mtx4 buf, x, y, z;
        	buf.init();
        	x.init();
        	y.init();
        	z.init();

        	x.m[1][1] = cs.v[0];	x.m[2][1] = -sn.v[0];
        	x.m[1][2] = sn.v[0];	x.m[2][2] = cs.v[0];

        	y.m[0][0] = cs.v[1];	y.m[2][0] = sn.v[1];
        	y.m[0][2] = -sn.v[1];	y.m[2][2] = cs.v[1];

        	z.m[0][0] = cs.v[2];	z.m[1][0] = -sn.v[2];
        	z.m[0][1] = sn.v[2];	z.m[1][1] = cs.v[2];

        	buf = x * y * z;
        	*this = buf;
	    }
};


#endif /* GL_MATH_H_ */
