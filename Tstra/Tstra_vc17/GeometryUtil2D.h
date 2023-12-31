#ifndef _INC_TSTRA_GEOMETRYUTIL2D
#define _INC_TSTRA_GEOMETRYUTIL2D

namespace tstra
{
	/// 平行束
	struct SParProjection
	{
		/// 射线方向
		float fRayX, fRayY;

		/// 探测器方向
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

	/// 扇束
	struct SFanProjection
	{
		/// 源
		float fSrcX, fSrcY;

		/// 探测器
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

	/**
	 * @brief 
	 * 
	 * @param iProjAngles 
	 * @param iProjDets 
	 * @param fDetSize 
	 * @param pfAngles 
	 * @param pfExtraOffsets 
	 * @return SParProjection* 
	 */
	SParProjection *genParProjections(unsigned int iProjAngles, unsigned int iProjDets, double fDetSize, const float *pfAngles, const float *pfExtraOffsets);
	/**
	 * @brief 
	 * 
	 * @param iProjAngles 
	 * @param iProjDets 
	 * @param fOriginSource 
	 * @param fOriginDetector 
	 * @param fDetSize 
	 * @param pfAngles 
	 * @param pfExtraOffsets 
	 * @return SFanProjection* 
	 */
	SFanProjection *genFanProjections(unsigned int iProjAngles, unsigned int iProjDets, double fOriginSource, double fOriginDetector, double fDetSize, const float *pfAngles, const float *pfExtraOffsets);
	/**
	 * @brief Get the Par Parameters object
	 * 
	 * @param proj 
	 * @param iProjDets 
	 * @param fAngle 
	 * @param fDetSize 
	 * @param fOffset 
	 * @return true 
	 * @return false 
	 */
	bool getParParameters(const SParProjection &proj, unsigned int iProjDets, float &fAngle, float &fDetSize, float &fOffset);
	/**
	 * @brief Get the Fan Parameters object
	 * 
	 * @param proj 
	 * @param iProjDets 
	 * @param fAngle 
	 * @param fOriginSource 
	 * @param fOriginDetector 
	 * @param fDetSize 
	 * @param fOffset 
	 * @return true 
	 * @return false 
	 */
	bool getFanParameters(const SFanProjection &proj, unsigned int iProjDets, float &fAngle, float &fOriginSource, float &fOriginDetector, float &fDetSize, float &fOffset);
}

#endif
