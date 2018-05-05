#include "stdafx.h"
#include "SpriteSystem.h"

SpriteSystem::SpriteSystem()
{
	mEffect.UpdateMatrixWorldToView(/*DirectX::XMMatrixLookAtLH(DirectX::XMVectorSet(0, 0, 100, 1.f), DirectX::XMVectorZero(), DirectX::XMVectorSet(0, 0, 1.f, 0))*/DirectX::XMMatrixIdentity());
	mEffect.UpdateMatrixViewToProj(/*DirectX::XMMatrixPerspectiveFovLH(0.25f*DirectX::XM_PI, 1920.f/1080.f, 1.0f, 1000.0f)*/DirectX::XMMatrixIdentity());

	D3D11_INPUT_ELEMENT_DESC vertexDesc[] =
	{
		{ "POSITION"	, 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD"	, 0, DXGI_FORMAT_R32G32_FLOAT, 0, 8, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	D3DX11_PASS_DESC passDesc = mEffect.GetPassDescriptionByIndex(0);
	HR(D3DUtil::gD3dDevice->CreateInputLayout(vertexDesc, 2, passDesc.pIAInputSignature, passDesc.IAInputSignatureSize, &mInputLayout));
	
	nsPlainEffect::Vertex vertices[] = {
		{ { 0.0f, 0.0f },{ 0.0f, 1.0f } },
		{ { 0.0f, 1.0f },{ 0.0f, 0.0f } },
		{ { 1.0f, 1.0f },{ 1.0f, 0.0f } },
		{ { 1.0f, 0.0f },{ 1.0f, 1.0f } }
	};
	Index indices[] =
	{
		0, 1, 2,
		0, 2, 3
	};

	mIndicesCount = ARRAYSIZE(indices);

	D3D11_BUFFER_DESC vbd;
	vbd.Usage = D3D11_USAGE_IMMUTABLE;
	vbd.ByteWidth = sizeof(nsPlainEffect::Vertex) * ARRAYSIZE(vertices);
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = 0;
	vbd.MiscFlags = 0;
	vbd.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA vid;
	vid.pSysMem = vertices;
	HR(D3DUtil::gD3dDevice->CreateBuffer(&vbd, &vid, &mVertexBuffer));
	D3D11_BUFFER_DESC ibd;
	ibd.Usage = D3D11_USAGE_IMMUTABLE;
	ibd.ByteWidth = sizeof(UINT) * mIndicesCount;
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;
	ibd.MiscFlags = 0;
	ibd.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA iid;
	iid.pSysMem = indices;
	HR(D3DUtil::gD3dDevice->CreateBuffer(&ibd, &iid, &mIndexBuffer));

	/*D3D11_RASTERIZER_DESC		rasterizeDescription;

	ZeroInitialize(rasterizeDescription);
	rasterizeDescription.FillMode = D3D11_FILL_WIREFRAME;
	rasterizeDescription.CullMode = D3D11_CULL_BACK;

	ID3D11RasterizerState* rasterizerState = nullptr;
	HR(D3DUtil::gD3dDevice->CreateRasterizerState(&rasterizeDescription, &rasterizerState));
	D3DUtil::gImmediateDeviceContext->RSSetState(rasterizerState);
	ReleaseCOM(rasterizerState);*/
}

SpriteSystem::~SpriteSystem()
{
	ReleaseCOM(mVertexBuffer);
	ReleaseCOM(mIndexBuffer);
	ReleaseCOM(mInputLayout);
}

void SpriteSystem::OperateEntities(EntityManager & entityManager, TimeSlotInSecond dt)
{
	using namespace D3DUtil;

	//指定背景色清空渲染对象视图
	float bgColor[] = { 0.8f, 0.6f, 0.4f, 1.0f };
	gImmediateDeviceContext->ClearRenderTargetView(gRenderTargetView, bgColor);
	gImmediateDeviceContext->ClearDepthStencilView(gDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	UINT stride = sizeof(nsPlainEffect::Vertex);
	UINT offset = 0;
	D3DUtil::gImmediateDeviceContext->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);
	D3DUtil::gImmediateDeviceContext->IASetIndexBuffer(mIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	gImmediateDeviceContext->IASetInputLayout(mInputLayout);
	gImmediateDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST); 
	for (Index i = 0; i < entityManager.entities.GetLength(); ++i) {
		if (!CanBeOperated(entityManager.entities[i])) {
			continue;
		}
		Point2D position = entityManager.mPositionComponents[i].position + entityManager.mSpriteComponents[i].offset;
		mEffect.UpdateMatrixLocalToWorld(DirectX::XMMatrixTranslation(position.x, position.y, 0));

		mEffect.UpdateSprite(SpriteFactory::gSpriteStore[entityManager.mSpriteComponents[i].spriteID].shaderResourceView);

		for (Index j = 0; j < mEffect.GetPassCount(); ++j) {
			mEffect.Apply(j);
			gImmediateDeviceContext->DrawIndexed(mIndicesCount, 0, 0);
		}
	}

	gSwapChain->Present(0, 0);
}
