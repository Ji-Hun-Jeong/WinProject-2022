#pragma once
class CTileMgr
{
	SINGLE(CTileMgr)
private:
	UINT	m_iTileXCount;
	UINT	m_iTileYCount;

	UINT	m_iTexTileXCount;
	UINT	m_iTexTileYCount;

	int		m_iCurIndex;
public:
	void Update();
	void SetTileCount(const UINT& _iX, const UINT& _iY) { m_iTileXCount = _iX; m_iTileYCount = _iY; }
	void SetCurIndex(const int& _iIdx) { m_iCurIndex = _iIdx; }

	const UINT& GetTileXCount() { return m_iTileXCount; }
	const UINT& GetTileYCount() { return m_iTileYCount; }
	const UINT& GetTexTileXCount() { return m_iTexTileXCount; }
	const UINT& GetTexTileYCount() { return m_iTexTileYCount; }
};

