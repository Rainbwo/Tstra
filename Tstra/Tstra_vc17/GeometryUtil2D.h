#ifndef _INC_TSTRA_GEOMETRYUTIL2D
#define _INC_TSTRA_GEOMETRYUTIL2D

namespace tstra
{
	/// ƽ����
	struct SParProjection
	{
		/// ���߷���
		float fRayX, fRayY;

		/// ̽��������
		float fDetSX, fDetSY;

		float fDetUX, fDetUY;

		void translate(double dx, double dy)
		{
			fDetSX += dx;
			fDetSY += dy;
		}

		void scale(double factor)
		{
			fRayX *= factor;
			fRayY *= factor;
			fDetSX *= factor;
			fDetSY *= factor;
			fDetUX *= factor;
			fDetUY *= factor;
		}
	};

	/// ����
	struct SFanProjection
	{
		/// Դ
		float fSrcX, fSrcY;

		/// ̽����
		float fDetSX, fDetSY;

		float fDetUX, fDetUY;

		void translate(double dx, double dy)
		{
			fSrcX += dx;
			fSrcY += dy;
			fDetSX += dx;
			fDetSY += dy;
		}

		void scale(double factor)
		{
			fSrcX *= factor;
			fSrcY *= factor;
			fDetSX *= factor;
			fDetSY *= factor;
			fDetUX *= factor;
			fDetUY *= factor;
		}
	};

	SParProjection *genParProjections(unsigned int iProjAngles, unsigned int iProjDets, double fDetSize, const float *pfAngles, const float *pfExtraOffsets);
	SFanProjection *genFanProjections(unsigned int iProjAngles, unsigned int iProjDets, double fOriginSource, double fOriginDetector, double fDetSize, const float *pfAngles, const float *pfExtraOffsets);

	bool getParParameters(const SParProjection &proj, unsigned int iProjDets, float &fAngle, float &fDetSize, float &fOffset);
	bool getFanParameters(const SFanProjection &proj, unsigned int iProjDets, float &fAngle, float &fOriginSource, float &fOriginDetector, float &fDetSize, float &fOffset);
}

#endif
